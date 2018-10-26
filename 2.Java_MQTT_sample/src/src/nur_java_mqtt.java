import com.nordicid.nurapi.NurApi;
import com.nordicid.nurapi.NurApiListener;
import com.nordicid.nurapi.NurApiSocketTransport;
import com.nordicid.nurapi.NurEventAutotune;
import com.nordicid.nurapi.NurEventClientInfo;
import com.nordicid.nurapi.NurEventDeviceInfo;
import com.nordicid.nurapi.NurEventEpcEnum;
import com.nordicid.nurapi.NurEventFrequencyHop;
import com.nordicid.nurapi.NurEventIOChange;
import com.nordicid.nurapi.NurEventInventory;
import com.nordicid.nurapi.NurEventNxpAlarm;
import com.nordicid.nurapi.NurEventProgrammingProgress;
import com.nordicid.nurapi.NurEventTagTrackingChange;
import com.nordicid.nurapi.NurEventTagTrackingData;
import com.nordicid.nurapi.NurEventTraceTag;
import com.nordicid.nurapi.NurEventTriggeredRead;
import com.nordicid.nurapi.NurTag;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class nur_java_mqtt {
    private static MqttClient mosquClient;
    private static MqttMessage  message = new MqttMessage();
    private static String topicctl      = "/nur_java_mqtt/ctl";
    private static String topicev       = "/nur_java_mqtt/events";
    private static String broker 		= "tcp://127.0.0.1:1883";
    private static String clientId     	= "nur_java_mqtt";
    private static String lastStatus   	= "N/A";

    private static NurApi mApi = new NurApi();

    // Init and connect to mqtt broker
    private static void initMqtt()
    {
        try {
            mosquClient = new MqttClient(broker, clientId);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            // Set this wrapper as the callback handler
            mosquClient.setCallback(mqttCallbacks);
            System.out.println("Connecting to broker: " + broker);
            mosquClient.connect(connOpts);
            System.out.println("Connected to broker");

            int qos = 0;
            mosquClient.subscribe(topicctl, qos);
        }
        catch(MqttException me) {
            System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
            System.exit(1);
        }
    }

    // Publish message to specific topic (catch by e.g. browser client)
    private static void publishMessage(String content, String topic)
    {
        try {
            message.setPayload(content.getBytes());
            mosquClient.publish(topic, message);
        }
        catch (MqttException me) {
            System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
            System.exit(2);
        }
    }

    // Publish status event
    private static void publishStatus(String status)
    {
        lastStatus = status;
        System.out.println("publishStatus() " + status);
        String statusJson = "{ \"type\": \"status\", \"msg\": \""+status+"\" }";
        publishMessage(statusJson, topicev);
    }

    // Publish inventoried tags
    private static void publishTags()
    {
        String tagsJson = "{ \"type\": \"tags\", \"tags\": [ ";
        synchronized (mApi.getStorage())
        {
            //System.out.println("publishTags() count " + mApi.getStorage().size());
            for (int n=0; n<mApi.getStorage().size(); n++)
            {
                if (n > 0)
                    tagsJson += ",";

                NurTag t = mApi.getStorage().get(n);
                tagsJson += "\"" + t.getEpcString() + "\"";
            }
            tagsJson += " ] }";
            mApi.getStorage().clear();
        }
        publishMessage(tagsJson, topicev);
    }

    // Connect nur reader over TCP/IP
    private static boolean connectNurIP(String addr, int port)
    {
        try {
            mApi.setTransport(new NurApiSocketTransport(addr, port));
            mApi.connect();
            return true;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {

        System.out.println("nur_java_mqtt main enter; NurApi v" + mApi.getFileVersion());

        //init mqtt for sending the results
        initMqtt();

        // Set listener for NurApi
        mApi.setListener(new NurApiListener() {
            @Override
            public void triggeredReadEvent(NurEventTriggeredRead arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void traceTagEvent(NurEventTraceTag arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void programmingProgressEvent(NurEventProgrammingProgress arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void logEvent(int arg0, String arg1) {
                // TODO Auto-generated method stub
            }

            @Override
            public void inventoryStreamEvent(NurEventInventory arg0) {
                // Got some tags
                if(arg0.tagsAdded != 0)
                {
                    publishTags();
                }

                if (arg0.stopped)
                {
                    // Restart stream
                    //System.out.println("Restart inventory stream");
                    try {
                        mApi.startInventoryStream();
                    } catch (Exception e)
                    {
                        publishStatus("error " + e.getMessage());
                    }
                }
            }

            @Override
            public void inventoryExtendedStreamEvent(NurEventInventory arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void frequencyHopEvent(NurEventFrequencyHop arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void disconnectedEvent() {
                // TODO Auto-generated method stub
            }

            @Override
            public void deviceSearchEvent(NurEventDeviceInfo arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void debugMessageEvent(String arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void connectedEvent() {
                // TODO Auto-generated method stub
            }

            @Override
            public void clientDisconnectedEvent(NurEventClientInfo arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void clientConnectedEvent(NurEventClientInfo arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void bootEvent(String arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void IOChangeEvent(NurEventIOChange arg0) {
                // TODO Auto-generated method stub
            }

            @Override
            public void autotuneEvent(NurEventAutotune arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void epcEnumEvent(NurEventEpcEnum arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void nxpEasAlarmEvent(NurEventNxpAlarm arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void tagTrackingChangeEvent(NurEventTagTrackingChange arg0) {
                // TODO Auto-generated method stub

            }

            @Override
            public void tagTrackingScanEvent(NurEventTagTrackingData arg0) {
                // TODO Auto-generated method stub

            }
        });

        while (true)
        {
            try {
                Thread.sleep(1000);
            } catch (Exception e)
            {
                break;
            }

            if (!mApi.isConnected())
            {
                publishStatus("no connection");
                if (!connectNurIP("127.0.0.1", 4333))
                {
                    publishStatus("connected");
                } else {
                    publishStatus("idle");
                }
            }

        }

        System.out.println("nur_java_mqtt main leave");
    }

    /****************************************************************/
    /* Methods to implement the MqttCallback interface              */
    /****************************************************************/

    private static MqttCallback mqttCallbacks = new MqttCallback()
    {

        @Override
        public void connectionLost(Throwable cause) {
            // Called when the connection to the server has been lost.
            // An application may choose to implement reconnection
            // logic at this point. This sample simply exits.
            System.out.println("Connection to " + broker + " lost!" + cause);
            System.exit(1);
        }

        /**
         * @see MqttCallback#deliveryComplete(IMqttDeliveryToken)
         */
        @Override
        public void deliveryComplete(IMqttDeliveryToken token) {
            // Called when a message has been delivered to the
            // server. The token passed in here is the same one
            // that was passed to or returned from the original call to publish.
            // This allows applications to perform asynchronous
            // delivery without blocking until delivery completes.
            //
            // This sample demonstrates asynchronous deliver and
            // uses the token.waitForCompletion() call in the main thread which
            // blocks until the delivery has completed.
            // Additionally the deliveryComplete method will be called if
            // the callback is set on the client
            //
            // If the connection to the server breaks before delivery has completed
            // delivery of a message will complete after the client has re-connected.
            // The getPendingTokens method will provide tokens for any messages
            // that are still to be delivered.
        }

        /**
         * @see MqttCallback#messageArrived(String, MqttMessage)
         */
        @Override
        public void messageArrived(String topic, MqttMessage message) throws MqttException {
            // Called when a message arrives from the server that matches any
            // subscription made by the client
            String msg = new String(message.getPayload());
            System.out.println("messageArrived() Topic:\t" + topic + "  Message:\t" + msg);

            if (msg.equals("status")) {
                publishStatus(lastStatus);
            }
            else if (msg.equals("stop")) {
                try {
                    mApi.stopInventoryStream();
                    publishStatus("idle");
                } catch(Exception e)
                {
                    publishStatus("error " + e.getMessage());
                }
            }
            else if (msg.equals("start")) {
                try {
                    mApi.startInventoryStream();
                    publishStatus("running");
                } catch(Exception e)
                {
                    publishStatus("error " + e.getMessage());
                }
            }
        }
    };

    /****************************************************************/
    /* End of MqttCallback methods                                  */
    /****************************************************************/
}
