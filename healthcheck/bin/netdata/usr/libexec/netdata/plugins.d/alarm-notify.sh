#!/usr/bin/env bash

# netdata
# real-time performance and health monitoring, done right!
# (C) 2016 Costa Tsaousis <costa@tsaousis.gr>
# GPL v3+
#
# Script to send alarm notifications for netdata
#
# Features:
#  - multiple notification methods
#  - multiple roles per alarm
#  - multiple recipients per role
#  - severity filtering per recipient
#
# Supported notification methods:
#  - emails
#  - slack.com notifications
#  - pushover.net notifications
#  - pushbullet.com push notifications by Tiago Peralta @tperalta82 PR #1070
#  - telegram.org notifications by @hashworks PR #1002
#  - twilio.com notifications by Levi Blaney @shadycuz PR #1211
#  - kafka notifications
#  - pagerduty.com notifications by Jim Cooley @jimcooley PR #1373

# -----------------------------------------------------------------------------
# testing notifications

if [ \( "${1}" = "test" -o "${2}" = "test" \) -a "${#}" -le 2 ]
then
    if [ "${2}" = "test" ]
    then
        recipient="${1}"
    else
        recipient="${2}"
    fi

    [ -z "${recipient}" ] && recipient="sysadmin"

    id=1
    last="CLEAR"
    for x in "CRITICAL" "WARNING" "CLEAR"
    do
        echo >&2
        echo >&2 "# SENDING TEST ${x} ALARM TO ROLE: ${recipient}"

        "${0}" "${recipient}" "$(hostname)" 1 1 "${id}" "$(date +%s)" "test_alarm" "test.chart" "test.family" "${x}" "${last}" 100 90 "${0}" 1 $((0 + id)) "units" "this is a test alarm to verify notifications work"
        if [ $? -ne 0 ]
        then
            echo >&2 "# FAILED"
        else
            echo >&2 "# OK"
        fi

        last="${x}"
        id=$((id + 1))
    done

    exit 1
fi

export PATH="${PATH}:/sbin:/usr/sbin:/usr/local/sbin"
export LC_ALL=C

# -----------------------------------------------------------------------------

PROGRAM_NAME="$(basename "${0}")"

logdate() {
    date "+%Y-%m-%d %H:%M:%S"
}

log() {
    local status="${1}"
    shift

    echo >&2 "$(logdate): ${PROGRAM_NAME}: ${status}: ${*}"

}

warning() {
    log WARNING "${@}"
}

error() {
    log ERROR "${@}"
}

info() {
    log INFO "${@}"
}

fatal() {
    log FATAL "${@}"
    exit 1
}

debug=0
debug() {
    [ ${debug} -eq 1 ] && log DEBUG "${@}"
}

# -----------------------------------------------------------------------------

# check for BASH v4+ (required for associative arrays)
[ $(( ${BASH_VERSINFO[0]} )) -lt 4 ] && \
    fatal "BASH version 4 or later is required (this is ${BASH_VERSION})."

# -----------------------------------------------------------------------------
# defaults to allow running this script by hand

NETDATA_CONFIG_DIR="${NETDATA_CONFIG_DIR-/etc/netdata}"
NETDATA_CACHE_DIR="${NETDATA_CACHE_DIR-/var/cache/netdata}"
[ -z "${NETDATA_REGISTRY_URL}" ] && NETDATA_REGISTRY_URL="https://registry.my-netdata.io"
[ -z "${NETDATA_HOSTNAME}" ] && NETDATA_HOSTNAME="$(hostname)"
[ -z "${NETDATA_REGISTRY_HOSTNAME}" ] && NETDATA_REGISTRY_HOSTNAME="${NETDATA_HOSTNAME}"

# -----------------------------------------------------------------------------
# parse command line parameters

roles="${1}"       # the roles that should be notified for this event
host="${2}"        # the host generated this event
unique_id="${3}"   # the unique id of this event
alarm_id="${4}"    # the unique id of the alarm that generated this event
event_id="${5}"    # the incremental id of the event, for this alarm id
when="${6}"        # the timestamp this event occurred
name="${7}"        # the name of the alarm, as given in netdata health.d entries
chart="${8}"       # the name of the chart (type.id)
family="${9}"      # the family of the chart
status="${10}"     # the current status : REMOVED, UNITIALIZED, UNDEFINED, CLEAR, WARNING, CRITICAL
old_status="${11}" # the previous status: REMOVED, UNITIALIZED, UNDEFINED, CLEAR, WARNING, CRITICAL
value="${12}"      # the current value of the alarm
old_value="${13}"  # the previous value of the alarm
src="${14}"        # the line number and file the alarm has been configured
duration="${15}"   # the duration in seconds of the previous alarm state
non_clear_duration="${16}" # the total duration in seconds this is/was non-clear
units="${17}"      # the units of the value
info="${18}"       # a short description of the alarm

# -----------------------------------------------------------------------------
# screen statuses we don't need to send a notification

# don't do anything if this is not WARNING, CRITICAL or CLEAR
if [ "${status}" != "WARNING" -a "${status}" != "CRITICAL" -a "${status}" != "CLEAR" ]
then
    info "not sending notification for ${status} on '${chart}.${name}'"
    exit 1
fi

# don't do anything if this is CLEAR, but it was not WARNING or CRITICAL
if [ "${old_status}" != "WARNING" -a "${old_status}" != "CRITICAL" -a "${status}" = "CLEAR" ]
then
    info "not sending notification for ${status} on '${chart}.${name}' (last status was ${old_status})"
    exit 1
fi

# -----------------------------------------------------------------------------
# load configuration

# By default fetch images from the global public registry.
# This is required by default, since all notification methods need to download
# images via the Internet, and private registries might not be reachable.
# This can be overwritten at the configuration file.
images_base_url="https://registry.my-netdata.io"

# needed commands
# if empty they will be searched in the system path
curl=
sendmail=

# enable / disable features
SEND_SLACK="YES"
SEND_PUSHOVER="YES"
SEND_TWILIO="YES"
SEND_TELEGRAM="YES"
SEND_EMAIL="YES"
SEND_PUSHBULLET="YES"
SEND_KAFKA="YES"
SEND_PD="YES"

# slack configs
SLACK_WEBHOOK_URL=
DEFAULT_RECIPIENT_SLACK=
declare -A role_recipients_slack=()

# pushover configs
PUSHOVER_APP_TOKEN=
DEFAULT_RECIPIENT_PUSHOVER=
declare -A role_recipients_pushover=()

# pushbullet configs
PUSHBULLET_ACCESS_TOKEN=
DEFAULT_RECIPIENT_PUSHBULLET=
declare -A role_recipients_pushbullet=()

# twilio configs
TWILIO_ACCOUNT_SID=
TWILIO_ACCOUNT_TOKEN=
TWILIO_NUMBER=
DEFAULT_RECIPIENT_TWILIO=
declare -A role_recipients_twilio=()

# telegram configs
TELEGRAM_BOT_TOKEN=
DEFAULT_RECIPIENT_TELEGRAM=
declare -A role_recipients_telegram=()

# kafka configs
KAFKA_URL=
KAFKA_SENDER_IP=

# pagerduty.com configs
PD_SERVICE_KEY=
declare -A role_recipients_pd=()

# email configs
DEFAULT_RECIPIENT_EMAIL="root"
declare -A role_recipients_email=()

# load the user configuration
# this will overwrite the variables above
if [ -f "${NETDATA_CONFIG_DIR}/health_alarm_notify.conf" ]
    then
    source "${NETDATA_CONFIG_DIR}/health_alarm_notify.conf"
fi

# -----------------------------------------------------------------------------
# filter a recipient based on alarm event severity

filter_recipient_by_criticality() {
    local method="${1}" x="${2}" r s
    shift

    r="${x/|*/}" # the recipient
    s="${x/*|/}" # the severity required for notifying this recipient

    # no severity filtering for this person
    [ "${r}" = "${s}" ] && return 0

    # the severity is invalid
    s="${s^^}"
    [ "${s}" != "CRITICAL" ] && return 0

    # the new or the old status matches the severity
    if [ "${s}" = "${status}" -o "${s}" = "${old_status}" ]
        then
        [ ! -d "${NETDATA_CACHE_DIR}/alarm-notify/${method}/${r}" ] && \
            mkdir -p "${NETDATA_CACHE_DIR}/alarm-notify/${method}/${r}"

        # we need to keep track of the notifications we sent
        # so that the same user will receive the recovery
        # even if old_status does not match the required severity
        touch "${NETDATA_CACHE_DIR}/alarm-notify/${method}/${r}/${alarm_id}"
        return 0
    fi

    # it is a cleared alarm we have sent notification for
    if [ "${status}" != "WARNING" -a "${status}" != "CRITICAL" -a -f "${NETDATA_CACHE_DIR}/alarm-notify/${method}/${r}/${alarm_id}" ]
        then
        rm "${NETDATA_CACHE_DIR}/alarm-notify/${method}/${r}/${alarm_id}"
        return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# find the recipients' addresses per method

declare -A arr_slack=()
declare -A arr_pushover=()
declare -A arr_pushbullet=()
declare -A arr_twilio=()
declare -A arr_telegram=()
declare -A arr_pd=()
declare -A arr_email=()

# netdata may call us with multiple roles, and roles may have multiple but
# overlapping recipients - so, here we find the unique recipients.
for x in ${roles//,/ }
do
    # the roles 'silent' and 'disabled' mean:
    # don't send a notification for this role
    [ "${x}" = "silent" -o "${x}" = "disabled" ] && continue

    # email
    a="${role_recipients_email[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_EMAIL}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality email "${r}" && arr_email[${r/|*/}]="1"
    done

    # pushover
    a="${role_recipients_pushover[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_PUSHOVER}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality pushover "${r}" && arr_pushover[${r/|*/}]="1"
    done

    # pushbullet
    a="${role_recipients_pushbullet[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_PUSHBULLET}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality pushbullet "${r}" && arr_pushbullet[${r/|*/}]="1"
    done

    # twilio
    a="${role_recipients_twilio[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_TWILIO}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality twilio "${r}" && arr_twilio[${r/|*/}]="1"
    done

    # telegram
    a="${role_recipients_telegram[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_TELEGRAM}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality telegram "${r}" && arr_telegram[${r/|*/}]="1"
    done

    # slack
    a="${role_recipients_slack[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_SLACK}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality slack "${r}" && arr_slack[${r/|*/}]="1"
    done

    # pagerduty.com
    a="${role_recipients_pd[${x}]}"
    [ -z "${a}" ] && a="${DEFAULT_RECIPIENT_PD}"
    for r in ${a//,/ }
    do
        [ "${r}" != "disabled" ] && filter_recipient_by_criticality pd "${r}" && arr_pd[${r/|*/}]="1"
    done
done

# build the list of slack recipients (channels)
to_slack="${!arr_slack[*]}"
[ -z "${to_slack}" ] && SEND_SLACK="NO"

# build the list of pushover recipients (user tokens)
to_pushover="${!arr_pushover[*]}"
[ -z "${to_pushover}" ] && SEND_PUSHOVER="NO"

# build the list of pushbulet recipients (user tokens)
to_pushbullet="${!arr_pushbullet[*]}"
[ -z "${to_pushbullet}" ] && SEND_PUSHBULLET="NO"

# build the list of twilio recipients (phone numbers)
to_twilio="${!arr_twilio[*]}"
[ -z "${to_twilio}" ] && SEND_TWILIO="NO"

# check array of telegram recipients (chat ids)
to_telegram="${!arr_telegram[*]}"
[ -z "${to_telegram}" ] && SEND_TELEGRAM="NO"

# build the list of pagerduty recipients (service keys)
to_pd="${!arr_pd[*]}"
[ -z "${to_pd}" ] && SEND_PD="NO"

# build the list of email recipients (email addresses)
to_email=
for x in "${!arr_email[@]}"
do
    [ ! -z "${to_email}" ] && to_email="${to_email}, "
    to_email="${to_email}${x}"
done
[ -z "${to_email}" ] && SEND_EMAIL="NO"


# -----------------------------------------------------------------------------
# verify the delivery methods supported

# check slack
[ -z "${SLACK_WEBHOOK_URL}" ] && SEND_SLACK="NO"

# check pushover
[ -z "${PUSHOVER_APP_TOKEN}" ] && SEND_PUSHOVER="NO"

# check pushbullet
[ -z "${PUSHBULLET_ACCESS_TOKEN}" ] && SEND_PUSHBULLET="NO"

# check twilio
[ -z "${TWILIO_ACCOUNT_TOKEN}" -o -z "${TWILIO_ACCOUNT_SID}" -o -z "${TWILIO_NUMBER}" ] && SEND_TWILIO="NO"

# check telegram
[ -z "${TELEGRAM_BOT_TOKEN}" ] && SEND_TELEGRAM="NO"

# check kafka
[ -z "${KAFKA_URL}" -o -z "${KAFKA_SENDER_IP}" ] && SEND_KAFKA="NO"

# check pagerduty.com
# if we need pd-send, check for the pd-send command
# https://www.pagerduty.com/docs/guides/agent-install-guide/
if [ "${SEND_PD}" = "YES" ]
    then
    pd_send="$(which pd-send 2>/dev/null || command -v pd-send 2>/dev/null)"
    if [ -z "${pd_send}" ]
        then
        # no pd-send available
        # disable pagerduty.com
        SEND_PD="NO"
    fi
fi

# if we need curl, check for the curl command
if [ \( "${SEND_PUSHOVER}" = "YES" -o "${SEND_SLACK}" = "YES" -o "${SEND_TWILIO}" = "YES" -o "${SEND_TELEGRAM}" = "YES" -o "${SEND_PUSHBULLET}" = "YES" -o "${SEND_KAFKA}" = "YES" \) -a -z "${curl}" ]
    then
    curl="$(which curl 2>/dev/null || command -v curl 2>/dev/null)"
    if [ -z "${curl}" ]
        then
        # no curl available
        # disable all curl based methods
        SEND_PUSHOVER="NO"
        SEND_PUSHBULLET="NO"
        SEND_TELEGRAM="NO"
        SEND_SLACK="NO"
        SEND_TWILIO="NO"
        SEND_KAFKA="NO"
    fi
fi

# if we need sendmail, check for the sendmail command
if [ "${SEND_EMAIL}" = "YES" -a -z "${sendmail}" ]
    then
    sendmail="$(which sendmail 2>/dev/null || command -v sendmail 2>/dev/null)"
    [ -z "${sendmail}" ] && SEND_EMAIL="NO"
fi

# check that we have at least a method enabled
if [   "${SEND_EMAIL}"      != "YES" \
    -a "${SEND_PUSHOVER}"   != "YES" \
    -a "${SEND_TELEGRAM}"   != "YES" \
    -a "${SEND_SLACK}"      != "YES" \
    -a "${SEND_TWILIO}"     != "YES" \
    -a "${SEND_PUSHBULLET}" != "YES" \
    -a "${SEND_KAFKA}"      != "YES" \
    -a "${SEND_PD}"         != "YES" \
    ]
    then
    fatal "All notification methods are disabled. Not sending notification to '${roles}' for '${name}' = '${value}' of chart '${chart}' for status '${status}'."
fi

# -----------------------------------------------------------------------------
# find a suitable hostname to use, if netdata did not supply a hostname

[ -z "${host}" ] && host="${NETDATA_HOSTNAME}"
[ -z "${host}" ] && host="${NETDATA_REGISTRY_HOSTNAME}"
[ -z "${host}" ] && host="$(hostname 2>/dev/null)"

# -----------------------------------------------------------------------------
# get the date the alarm happened

date="$(date --date=@${when} 2>/dev/null)"
[ -z "${date}" ] && date="$(date 2>/dev/null)"

# -----------------------------------------------------------------------------
# function to URL encode a string

urlencode() {
    local string="${1}" strlen encoded pos c o

    strlen=${#string}
    for (( pos=0 ; pos<strlen ; pos++ ))
    do
        c=${string:${pos}:1}
        case "${c}" in
            [-_.~a-zA-Z0-9])
                o="${c}"
                ;;

            *)
                printf -v o '%%%02x' "'${c}"
                ;;
        esac
        encoded+="${o}"
    done

    REPLY="${encoded}"
    echo "${REPLY}"
}

# -----------------------------------------------------------------------------
# function to convert a duration in seconds, to a human readable duration
# using DAYS, MINUTES, SECONDS

duration4human() {
    local s="${1}" d=0 h=0 m=0 ds="day" hs="hour" ms="minute" ss="second" ret
    d=$(( s / 86400 ))
    s=$(( s - (d * 86400) ))
    h=$(( s / 3600 ))
    s=$(( s - (h * 3600) ))
    m=$(( s / 60 ))
    s=$(( s - (m * 60) ))

    if [ ${d} -gt 0 ]
    then
        [ ${m} -ge 30 ] && h=$(( h + 1 ))
        [ ${d} -gt 1 ] && ds="days"
        [ ${h} -gt 1 ] && hs="hours"
        if [ ${h} -gt 0 ]
        then
            ret="${d} ${ds} and ${h} ${hs}"
        else
            ret="${d} ${ds}"
        fi
    elif [ ${h} -gt 0 ]
    then
        [ ${s} -ge 30 ] && m=$(( m + 1 ))
        [ ${h} -gt 1 ] && hs="hours"
        [ ${m} -gt 1 ] && ms="minutes"
        if [ ${m} -gt 0 ]
        then
            ret="${h} ${hs} and ${m} ${ms}"
        else
            ret="${h} ${hs}"
        fi
    elif [ ${m} -gt 0 ]
    then
        [ ${m} -gt 1 ] && ms="minutes"
        [ ${s} -gt 1 ] && ss="seconds"
        if [ ${s} -gt 0 ]
        then
            ret="${m} ${ms} and ${s} ${ss}"
        else
            ret="${m} ${ms}"
        fi
    else
        [ ${s} -gt 1 ] && ss="seconds"
        ret="${s} ${ss}"
    fi

    REPLY="${ret}"
    echo "${REPLY}"
}

# -----------------------------------------------------------------------------
# email sender

send_email() {
    local ret=
    if [ "${SEND_EMAIL}" = "YES" ]
        then

        "${sendmail}" -t
        ret=$?

        if [ ${ret} -eq 0 ]
        then
            info "sent email notification for: ${host} ${chart}.${name} is ${status} to '${to_email}'"
            return 0
        else
            error "failed to send email notification for: ${host} ${chart}.${name} is ${status} to '${to_email}' with error code ${ret}."
            return 1
        fi
    fi

    return 1
}

# -----------------------------------------------------------------------------
# pushover sender

send_pushover() {
    local apptoken="${1}" usertokens="${2}" when="${3}" url="${4}" status="${5}" title="${6}" message="${7}" httpcode sent=0 user priority

    if [ "${SEND_PUSHOVER}" = "YES" -a ! -z "${apptoken}" -a ! -z "${usertokens}" -a ! -z "${title}" -a ! -z "${message}" ]
        then

        # https://pushover.net/api
        priority=-2
        case "${status}" in
            CLEAR) priority=-1;;   # low priority: no sound or vibration
            WARNING) priotity=0;;  # normal priority: respect quiet hours
            CRITICAL) priority=1;; # high priority: bypass quiet hours
            *) priority=-2;;       # lowest priority: no notification at all
        esac

        for user in ${usertokens}
        do
            httpcode=$(${curl} --write-out %{http_code} --silent --output /dev/null \
                --form-string "token=${apptoken}" \
                --form-string "user=${user}" \
                --form-string "html=1" \
                --form-string "title=${title}" \
                --form-string "message=${message}" \
                --form-string "timestamp=${when}" \
                --form-string "url=${url}" \
                --form-string "url_title=Open netdata dashboard to view the alarm" \
                --form-string "priority=${priority}" \
                https://api.pushover.net/1/messages.json)

            if [ "${httpcode}" == "200" ]
            then
                info "sent pushover notification for: ${host} ${chart}.${name} is ${status} to '${user}'"
                sent=$((sent + 1))
            else
                error "failed to send pushover notification for: ${host} ${chart}.${name} is ${status} to '${user}' with HTTP error code ${httpcode}."
            fi
        done

        [ ${sent} -gt 0 ] && return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# pushbullet sender

send_pushbullet() {
    local userapikey="${1}" recipients="${2}"  title="${3}" message="${4}" httpcode sent=0 user
    if [ "${SEND_PUSHBULLET}" = "YES" -a ! -z "${userapikey}" -a ! -z "${recipients}" -a ! -z "${message}" -a ! -z "${title}" ]
        then
        #https://docs.pushbullet.com/#create-push
        for user in ${recipients}
        do
            httpcode=$(${curl} --write-out %{http_code} --silent --output /dev/null \
              --header 'Access-Token: '${userapikey}'' \
              --header 'Content-Type: application/json' \
              --data-binary  @<(cat <<EOF
                              {"title": "${title}",
                              "type": "note",
                              "email": "${user}",
                              "body": "$( echo -n ${message})"}
EOF
               ) "https://api.pushbullet.com/v2/pushes" -X POST)

            if [ "${httpcode}" == "200" ]
            then
                info "sent pushbullet notification for: ${host} ${chart}.${name} is ${status} to '${user}'"
                sent=$((sent + 1))
            else
                error "failed to send pushbullet notification for: ${host} ${chart}.${name} is ${status} to '${user}' with HTTP error code ${httpcode}."
            fi
        done

        [ ${sent} -gt 0 ] && return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# kafka sender

send_kafka() {
    local httpcode sent=0 
    if [ "${SEND_KAFKA}" = "YES" ]
        then
            httpcode=$(${curl} -X POST --write-out %{http_code} --silent --output /dev/null \
                --data "{host_ip:\"${KAFKA_SENDER_IP}\",when:${when},name:\"${name}\",chart:\"${chart}\",family:\"${family}\",status:\"${status}\",old_status:\"${old_status}\",value:${value},old_value:${old_value},duration:${duration},non_clear_duration:${non_clear_duration},units:\"${units}\",info:\"${info}\"}" \
                "${KAFKA_URL}")

            if [ "${httpcode}" == "204" ]
            then
                info "sent kafka data for: ${host} ${chart}.${name} is ${status} and ip '${KAFKA_SENDER_IP}'"
                sent=$((sent + 1))
            else
                error "failed to send kafka data for: ${host} ${chart}.${name} is ${status} and ip '${KAFKA_SENDER_IP}' with HTTP error code ${httpcode}."
            fi

        [ ${sent} -gt 0 ] && return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# pagerduty.com sender

send_pd() {
    local recipients="${1}" sent=0
    unset t
    case ${status} in
        CLEAR)    t='resolve';;
        WARNING)  t='trigger';;
        CRITICAL) t='trigger';;
    esac

    if [ ${SEND_PD} = "YES" -a ! -z "${t}" ]
        then
        for PD_SERVICE_KEY in ${recipients}
        do
            d="${status} ${name}=${value} ${units} - ${host}, ${family}"
            ${pd_send} -k ${PD_SERVICE_KEY} \
                       -t ${t} \
                       -d "${d}" \
                       -i ${alarm_id} \
                       -f 'info'="${info}" \
                       -f 'value_w_units'="${value} ${units}" \
                       -f 'when'="${when}" \
                       -f 'duration'="${duration}" \
                       -f 'roles'="${roles}" \
                       -f 'host'="${host}" \
                       -f 'unique_id'="${unique_id}" \
                       -f 'alarm_id'="${alarm_id}" \
                       -f 'event_id'="${event_id}" \
                       -f 'name'="${name}" \
                       -f 'chart'="${chart}" \
                       -f 'family'="${family}" \
                       -f 'status'="${status}" \
                       -f 'old_status'="${old_status}" \
                       -f 'value'="${value}" \
                       -f 'old_value'="${old_value}" \
                       -f 'src'="${src}" \
                       -f 'non_clear_duration'="${non_clear_duration}" \
                       -f 'units'="${units}"
            retval=$?
            if [ ${retval} -eq 0 ]
                then
                    info "sent pagerduty.com notification using service key ${PD_SERVICE_KEY::-26}....: ${d}"
                    sent=$((sent + 1))
                else
                    error "failed to send pagerduty.com notification using service key ${PD_SERVICE_KEY::-26}.... (error code ${retval}): ${d}"
            fi
        done

        [ ${sent} -gt 0 ] && return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# twilio sender

send_twilio() {
    local accountsid="${1}" accounttoken="${2}" twilionumber="${3}" recipients="${4}"  title="${5}" message="${6}" httpcode sent=0 user
    if [ "${SEND_TWILIO}" = "YES" -a ! -z "${accountsid}" -a ! -z "${accounttoken}" -a ! -z "${twilionumber}" -a ! -z "${recipients}" -a ! -z "${message}" -a ! -z "${title}" ]
        then
        #https://www.twilio.com/packages/labs/code/bash/twilio-sms
        for user in ${recipients}
        do
            httpcode=$(${curl} -X POST --write-out %{http_code} --silent --output /dev/null \
                --data-urlencode "From=${twilionumber}" \
                --data-urlencode "To=${user}" \
                --data-urlencode "Body=${title} ${message}" \
                -u "${accountsid}:${accounttoken}" \
                "https://api.twilio.com/2010-04-01/Accounts/${accountsid}/Messages.json")

            if [ "${httpcode}" == "201" ]
            then
                info "sent Twilio SMS for: ${host} ${chart}.${name} is ${status} to '${user}'"
                sent=$((sent + 1))
            else
                error "failed to send Twilio SMS for: ${host} ${chart}.${name} is ${status} to '${user}' with HTTP error code ${httpcode}."
            fi
        done

        [ ${sent} -gt 0 ] && return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# telegram sender

send_telegram() {
    local bottoken="${1}" chatids="${2}" message="${3}" httpcode sent=0 chatid disableNotification=""

    if [ "${status}" = "CLEAR" ]; then disableNotification="--data-urlencode disable_notification=true"; fi

    if [ "${SEND_TELEGRAM}" = "YES" -a ! -z "${bottoken}" -a ! -z "${chatids}" -a ! -z "${message}" ];
    then
        for chatid in ${chatids}
        do
            # https://core.telegram.org/bots/api#sendmessage
            httpcode=$(${curl} --write-out %{http_code} --silent --output /dev/null ${disableNotification} \
                --data-urlencode "parse_mode=HTML" \
                --data-urlencode "disable_web_page_preview=true" \
                --data-urlencode "text=${message}" \
                "https://api.telegram.org/bot${bottoken}/sendMessage?chat_id=${chatid}")

            if [ "${httpcode}" == "200" ]
            then
                info "sent telegram notification for: ${host} ${chart}.${name} is ${status} to '${chatid}'"
                sent=$((sent + 1))
            elif [ "${httpcode}" == "401" ]
            then
                error "failed to send telegram notification for: ${host} ${chart}.${name} is ${status} to '${chatid}': Wrong bot token."
            else
                error "failed to send telegram notification for: ${host} ${chart}.${name} is ${status} to '${chatid}' with HTTP error code ${httpcode}."
            fi
        done

        [ ${sent} -gt 0 ] && return 0
    fi

    return 1
}

# -----------------------------------------------------------------------------
# slack sender

send_slack() {
    local webhook="${1}" channels="${2}" httpcode sent=0 channel color payload

    [ "${SEND_SLACK}" != "YES" ] && return 1

    case "${status}" in
        WARNING)  color="warning" ;;
        CRITICAL) color="danger" ;;
        CLEAR)    color="good" ;;
        *)        color="#777777" ;;
    esac

    for channel in ${channels}
    do
        payload="$(cat <<EOF
        {
            "channel": "#${channel}",
            "username": "netdata on ${host}",
            "icon_url": "${images_base_url}/images/seo-performance-128.png",
            "text": "${host} ${status_message}, \`${chart}\` (_${family}_), *${alarm}*",
            "attachments": [
                {
                    "fallback": "${alarm} - ${chart} (${family}) - ${info}",
                    "color": "${color}",
                    "title": "${alarm}",
                    "title_link": "${goto_url}",
                    "text": "${info}",
                    "fields": [
                        {
                            "title": "${chart}",
                            "short": true
                        },
                        {
                            "title": "${family}",
                            "short": true
                        }
                    ],
                    "thumb_url": "${image}",
                    "footer": "<${goto_url}|${host}>",
                    "ts": ${when}
                }
            ]
        }
EOF
        )"

        httpcode=$(${curl} --write-out %{http_code} --silent --output /dev/null -X POST --data-urlencode "payload=${payload}" "${webhook}")
        if [ "${httpcode}" == "200" ]
        then
            info "sent slack notification for: ${host} ${chart}.${name} is ${status} to '${channel}'"
            sent=$((sent + 1))
        else
            error "failed to send slack notification for: ${host} ${chart}.${name} is ${status} to '${channel}', with HTTP error code ${httpcode}."
        fi
    done

    [ ${sent} -gt 0 ] && return 0

    return 1
}


# -----------------------------------------------------------------------------
# prepare the content of the notification

# the url to send the user on click
urlencode "${NETDATA_REGISTRY_HOSTNAME}" >/dev/null; url_host="${REPLY}"
urlencode "${chart}" >/dev/null; url_chart="${REPLY}"
urlencode "${family}" >/dev/null; url_family="${REPLY}"
urlencode "${name}" >/dev/null; url_name="${REPLY}"
goto_url="${NETDATA_REGISTRY_URL}/goto-host-from-alarm.html?host=${url_host}&chart=${url_chart}&family=${url_family}&alarm=${url_name}&alarm_unique_id=${unique_id}&alarm_id=${alarm_id}&alarm_event_id=${event_id}"

# the severity of the alarm
severity="${status}"

# the time the alarm was raised
duration4human ${duration} >/dev/null; duration_txt="${REPLY}"
duration4human ${non_clear_duration} >/dev/null; non_clear_duration_txt="${REPLY}"
raised_for="(was ${old_status,,} for ${duration_txt})"

# the key status message
status_message="status unknown"

# the color of the alarm
color="grey"

# the alarm value
alarm="${name//_/ } = ${value} ${units}"

# the image of the alarm
image="${images_base_url}/images/seo-performance-128.png"

# prepare the title based on status
case "${status}" in
	CRITICAL)
        image="${images_base_url}/images/alert-128-red.png"
        status_message="is critical"
        color="#ca414b"
        ;;

    WARNING)
        image="${images_base_url}/images/alert-128-orange.png"
        status_message="needs attention"
        color="#caca4b"
		;;

	CLEAR)
        image="${images_base_url}/images/check-mark-2-128-green.png"
    	status_message="recovered"
		color="#77ca6d"
		;;
esac

if [ "${status}" = "CLEAR" ]
then
    severity="Recovered from ${old_status}"
    if [ ${non_clear_duration} -gt ${duration} ]
    then
        raised_for="(alarm was raised for ${non_clear_duration_txt})"
    fi

    # don't show the value when the status is CLEAR
    # for certain alarms, this value might not have any meaning
    alarm="${name//_/ } ${raised_for}"

elif [ "${old_status}" = "WARNING" -a "${status}" = "CRITICAL" ]
then
    severity="Escalated to ${status}"
    if [ ${non_clear_duration} -gt ${duration} ]
    then
        raised_for="(alarm is raised for ${non_clear_duration_txt})"
    fi

elif [ "${old_status}" = "CRITICAL" -a "${status}" = "WARNING" ]
then
    severity="Demoted to ${status}"
    if [ ${non_clear_duration} -gt ${duration} ]
    then
        raised_for="(alarm is raised for ${non_clear_duration_txt})"
    fi

else
    raised_for=
fi

# prepare HTML versions of elements
info_html=
[ ! -z "${info}" ] && info_html=" <small><br/>${info}</small>"

raised_for_html=
[ ! -z "${raised_for}" ] && raised_for_html="<br/><small>${raised_for}</small>"

# -----------------------------------------------------------------------------
# send the slack notification

# slack aggregates posts from the same username
# so we use "${host} ${status}" as the bot username, to make them diff

send_slack "${SLACK_WEBHOOK_URL}" "${to_slack}"
SENT_SLACK=$?

# -----------------------------------------------------------------------------
# send the pushover notification

send_pushover "${PUSHOVER_APP_TOKEN}" "${to_pushover}" "${when}" "${goto_url}" "${status}" "${host} ${status_message} - ${name//_/ } - ${chart}" "
<font color=\"${color}\"><b>${alarm}</b></font>${info_html}<br/>&nbsp;
<small><b>${chart}</b><br/>Chart<br/>&nbsp;</small>
<small><b>${family}</b><br/>Family<br/>&nbsp;</small>
<small><b>${severity}</b><br/>Severity<br/>&nbsp;</small>
<small><b>${date}${raised_for_html}</b><br/>Time<br/>&nbsp;</small>
<a href=\"${goto_url}\">View Netdata</a><br/>&nbsp;
<small><small>The source of this alarm is line ${src}</small></small>
"

SENT_PUSHOVER=$?

# -----------------------------------------------------------------------------
# send the pushbullet notification

send_pushbullet "${PUSHBULLET_ACCESS_TOKEN}" "${to_pushbullet}" "${host} ${status_message} - ${name//_/ } - ${chart}" "${alarm}\n
Severity: ${severity}\n
Chart: ${chart}\n
Family: ${family}\n
To View Netdata go to: ${goto_url}\n
The source of this alarm is line ${src}"

SENT_PUSHBULLET=$?

# -----------------------------------------------------------------------------
# send the twilio SMS

send_twilio "${TWILIO_ACCOUNT_SID}" "${TWILIO_ACCOUNT_TOKEN}" "${TWILIO_NUMBER}" "${to_twilio}" "${host} ${status_message} - ${name//_/ } - ${chart}" "${alarm} 
Severity: ${severity}
Chart: ${chart}
Family: ${family}
${info}"

SENT_TWILIO=$?

# -----------------------------------------------------------------------------
# send the telegram.org message

# https://core.telegram.org/bots/api#formatting-options
send_telegram "${TELEGRAM_BOT_TOKEN}" "${to_telegram}" "${host} ${status_message} - <b>${name//_/ }</b>
${chart} (${family})
<a href=\"${goto_url}\">${alarm}</a>
<i>${info}</i>"

SENT_TELEGRAM=$?


# -----------------------------------------------------------------------------
# send the kafka message

send_kafka
SENT_KAFKA=$?


# -----------------------------------------------------------------------------
# send the pagerduty.com message

send_pd "${to_pd}"
SENT_PD=$?


# -----------------------------------------------------------------------------
# send the email

send_email <<EOF
To: ${to_email}
Subject: ${host} ${status_message} - ${name//_/ } - ${chart}
Content-Type: text/html

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; box-sizing: border-box; font-size: 14px; margin: 0; padding: 0;">
<body style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 14px; width: 100% !important; min-height: 100%; line-height: 1.6; background: #f6f6f6; margin:0; padding: 0;">
<table>
    <tbody>
    <tr>
        <td style="vertical-align: top;" valign="top"></td>
        <td width="700" style="vertical-align: top; display: block !important; max-width: 700px !important; clear: both !important; margin: 0 auto; padding: 0;" valign="top">
            <div style="max-width: 700px; display: block; margin: 0 auto; padding: 20px;">
                <table width="100%" cellpadding="0" cellspacing="0" style="background: #fff; border: 1px solid #e9e9e9;">
                    <tbody>
                    <tr>
                        <td bgcolor="#eee" style="padding: 5px 20px 5px 20px; background-color: #eee;">
                            <div style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 20px; color: #777; font-weight: bold;">netdata notification</div>
                        </td>
                    </tr>
                    <tr>
                        <td bgcolor="${color}" style="font-size: 16px; vertical-align: top; font-weight: 400; text-align: center; margin: 0; padding: 10px; color: #ffffff; background: ${color} !important; border: 1px solid ${color}; border-top-color: ${color};" align="center" valign="top">
                            <h1 style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-weight: 400; margin: 0;">${host} ${status_message}</h1>
                        </td>
                    </tr>
                    <tr>
                        <td style="vertical-align: top;" valign="top">
                            <div style="margin: 0; padding: 20px; max-width: 700px;">
                                <table width="100%" cellpadding="0" cellspacing="0" style="max-width:700px">
                                    <tbody>
                                    <tr>
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 18px; vertical-align: top; margin: 0; padding:0 0 20px;" align="left" valign="top">
                                            <span>${chart}</span>
                                            <span style="display: block; color: #666666; font-size: 12px; font-weight: 300; line-height: 1; text-transform: uppercase;">Chart</span>
                                        </td>
                                    </tr>
                                    <tr style="margin: 0; padding: 0;">
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 18px; vertical-align: top; margin: 0; padding: 0 0 20px;" align="left" valign="top">
                                            <span><b>${alarm}</b>${info_html}</span>
                                            <span style="display: block; color: #666666; font-size: 12px; font-weight: 300; line-height: 1; text-transform: uppercase;">Alarm</span>
                                        </td>
                                    </tr>
                                    <tr>
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 18px; vertical-align: top; margin: 0; padding: 0 0 20px;" align="left" valign="top">
                                            <span>${family}</span>
                                            <span style="display: block; color: #666666; font-size: 12px; font-weight: 300; line-height: 1; text-transform: uppercase;">Family</span>
                                        </td>
                                    </tr>
                                    <tr style="margin: 0; padding: 0;">
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 18px; vertical-align: top; margin: 0; padding: 0 0 20px;" align="left" valign="top">
                                            <span>${severity}</span>
                                            <span style="display: block; color: #666666; font-size: 12px; font-weight: 300; line-height: 1; text-transform: uppercase;">Severity</span>
                                        </td>
                                    </tr>
                                    <tr style="margin: 0; padding: 0;">
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 18px; vertical-align: top; margin: 0; padding: 0 0 20px;" align="left" valign="top"><span>${date}</span>
                                            <span>${raised_for_html}</span> <span style="display: block; color: #666666; font-size: 12px; font-weight: 300; line-height: 1; text-transform: uppercase;">Time</span>
                                        </td>
                                    </tr>
                                    <tr style="margin: 0; padding: 0;">
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 18px; vertical-align: top; margin: 0; padding: 0 0 20px;">
                                            <a href="${goto_url}" style="font-size: 14px; color: #ffffff; text-decoration: none; line-height: 1.5; font-weight: bold; text-align: center; display: inline-block; text-transform: capitalize; background: #35568d; border-width: 1px; border-style: solid; border-color: #2b4c86; margin: 0; padding: 10px 15px;" target="_blank">View Netdata</a>
                                        </td>
                                    </tr>
                                    <tr style="text-align: center; margin: 0; padding: 0;">
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 11px; vertical-align: top; margin: 0; padding: 10px 0 0 0; color: #666666;" align="center" valign="bottom">The source of this alarm is line <code>${src}</code>
                                        </td>
                                    </tr>
                                    <tr style="text-align: center; margin: 0; padding: 0;">
                                        <td style="font-family: 'Helvetica Neue', 'Helvetica', Helvetica, Arial, sans-serif; font-size: 12px; vertical-align: top; margin:0; padding: 20px 0 0 0; color: #666666; border-top: 1px solid #f0f0f0;" align="center" valign="bottom">Sent by
                                            <a href="https://mynetdata.io/" target="_blank">netdata</a>, the real-time performance monitoring.
                                        </td>
                                    </tr>
                                    </tbody>
                                </table>
                            </div>
                        </td>
                    </tr>
                    </tbody>
                </table>
            </div>
        </td>
    </tr>
    </tbody>
</table>
</body>
</html>
EOF

SENT_EMAIL=$?

# -----------------------------------------------------------------------------
# let netdata know

if [   ${SENT_EMAIL}      -eq 0 \
    -o ${SENT_PUSHOVER}   -eq 0 \
    -o ${SENT_TELEGRAM}   -eq 0 \
    -o ${SENT_SLACK}      -eq 0 \
    -o ${SENT_TWILIO}     -eq 0 \
    -o ${SENT_PUSHBULLET} -eq 0 \
    -o ${SENT_KAFKA}      -eq 0 \
    -o ${SENT_PD}         -eq 0 \
    ]
    then
    # we did send something
    exit 0
fi

# we did not send anything
exit 1
