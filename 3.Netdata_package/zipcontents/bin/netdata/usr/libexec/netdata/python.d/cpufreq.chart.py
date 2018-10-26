# -*- coding: utf-8 -*-
# Description: cpufreq netdata python.d module
# Author: Pawel Krupa (paulfantom) and Steven Noonan (tycho)

import glob
import os
import time
from base import SimpleService

# default module values (can be overridden per job in `config`)
# update_every = 2

ORDER = ['cpufreq']

CHARTS = {
    'cpufreq': {
        'options': [None, 'CPU Clock', 'MHz', 'cpufreq', None, 'line'],
        'lines': [
            # lines are created dynamically in `check()` method
        ]}
}

class Service(SimpleService):
    def __init__(self, configuration=None, name=None):
        prefix = os.getenv('NETDATA_HOST_PREFIX', "")
        if prefix.endswith('/'):
            prefix = prefix[:-1]
        self.sys_dir = prefix + "/sys/devices"
        SimpleService.__init__(self, configuration=configuration, name=name)
        self.order = ORDER
        self.definitions = CHARTS
        self._orig_name = ""
        self.assignment = {}
        self.accurate_exists = True
        self.accurate_last = {}

    def _get_data(self):
        data = {}

        if self.accurate_exists:
            elapsed = time.time() - self.timetable['last']

            accurate_ok = True

            for name, paths in self.assignment.items():
                last = self.accurate_last[name]
                current = 0
                for line in open(paths['accurate'], 'r'):
                    line = list(map(int, line.split()))
                    current += (line[0] * line[1]) / 100
                delta = current - last
                data[name] = delta
                self.accurate_last[name] = current
                if delta == 0 or abs(delta) > 1e7:
                    # Delta is either too large or nonexistent, fall back to
                    # less accurate reading. This can happen if we switch
                    # to/from the 'schedutil' governor, which doesn't report
                    # stats.
                    accurate_ok = False

            if accurate_ok:
                return data
            else:
                self.alert("accurate method failed, falling back")


        for name, paths in self.assignment.items():
            data[name] = open(paths['inaccurate'], 'r').read()

        return data

    def check(self):
        try:
            self.sys_dir = str(self.configuration['sys_dir'])
        except (KeyError, TypeError):
            self.error("No path specified. Using: '" + self.sys_dir + "'")

        self._orig_name = self.chart_name

        for path in glob.glob(self.sys_dir + '/system/cpu/cpu*/cpufreq/stats/time_in_state'):
            path_elem = path.split('/')
            cpu = path_elem[-4]
            if cpu not in self.assignment:
                self.assignment[cpu] = {}
            self.assignment[cpu]['accurate'] = path
            self.accurate_last[cpu] = 0

        if len(self.assignment) == 0:
            self.accurate_exists = False

        for path in glob.glob(self.sys_dir + '/system/cpu/cpu*/cpufreq/scaling_cur_freq'):
            path_elem = path.split('/')
            cpu = path_elem[-3]
            if cpu not in self.assignment:
                self.assignment[cpu] = {}
            self.assignment[cpu]['inaccurate'] = path

        if len(self.assignment) == 0:
            self.error("couldn't find a method to read cpufreq statistics")
            return False

        for name in self.assignment.keys():
            self.definitions[ORDER[0]]['lines'].append([name, name, 'absolute', 1, 1000])

        return True

    def create(self):
        self.chart_name = "cpu"
        status = SimpleService.create(self)
        self.chart_name = self._orig_name
        return status

    def update(self, interval):
        self.chart_name = "cpu"
        status = SimpleService.update(self, interval=interval)
        self.chart_name = self._orig_name
        return status
