
import com.nordicid.nurapi.NurApi;
import com.nordicid.nurapi.NurApiException;
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
import com.nordicid.nurapi.NurRespInventory;
import com.nordicid.nurapi.NurTag;
import com.nordicid.nurapi.NurTagStorage;

import java.io.IOException;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class javasample_ar8x {
	private static MqttClient mosquClient;
	private static MqttMessage  message = new MqttMessage();
	private static String topicev        = "javasample/events";
	private static String topictags       = "javasample/tags";
	private static String broker = "tcp://127.0.0.1:1883";
	private static String clientId     = "JavaSample";
	
    private static void initMqtt()
    {
    	try {
			mosquClient = new MqttClient(broker, clientId);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: "+broker);
            mosquClient.connect(connOpts);
            System.out.println("Connected");
        } catch(MqttException me) {
            System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
            System.exit(1);
        }
    }
    private static void cleanUp()
    {    	
    	try
		{
			mosquClient.disconnect();
			System.out.println("Disconnected");	
		} catch (MqttException me) {
			System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
            System.exit(1);
		}
    }
    
    private static void publishMessage(String content, String topic)
	{
		try {
			System.out.println(content);
			message.setPayload(content.getBytes());
			mosquClient.publish(topic, message);
			System.out.println("Message published");
		} catch (MqttException me) {
			// TODO Auto-generated catch block
			System.out.println("reason "+me.getReasonCode());
            System.out.println("msg "+me.getMessage());
            System.out.println("loc "+me.getLocalizedMessage());
            System.out.println("cause "+me.getCause());
            System.out.println("excep "+me);
            me.printStackTrace();
            System.exit(2);
		}
	}
    
	public static void main(String[] args) {
		
        
		System.out.println("javasample_ar8x main enter");
		//init mqtt for sending the results
		initMqtt();
		publishMessage("javasample started and MQTT client initialized", topicev);
		
		// Create a new NurApi object
		final NurApi mApi = new NurApi();
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
						// TODO Auto-generated method stub
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
						// We receive disconnected event when NurApi transport is disconnected
						System.out.println("disconnectedEvent()");
						System.exit(1);
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
						// We receive connected event when NurApi transport is connected
						publishMessage("connectedEvent()", topicev);
						try {
							mApi.clearIdBuffer();
							
							NurRespInventory resp = mApi.inventory();
							
							System.out.println("Inventory found " + resp.numTagsFound + " tags");
							publishMessage("Inventory found " + resp.numTagsFound + " tags", topicev);
							
							if(resp.numTagsFound > 0)
							{
								mApi.fetchTags();
								
								NurTagStorage tagStorage = mApi.getStorage();
								
								for (int i = 0; i < tagStorage.size(); i++) {
									
									NurTag tag = tagStorage.get(i);		
									publishMessage(tag.getEpcString(), topictags);
								}
							}
						} catch (Exception e) { 
							e.printStackTrace();
							publishMessage("Error during inventory " + e.getMessage(), topicev);
						}
						publishMessage("javasample exiting", topicev);
						cleanUp();
						
						try {
							mApi.disconnect();
						} catch (Exception e) {
							e.printStackTrace();
						}
						System.exit(0);
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
				

				String nurDevice = "127.0.0.1";
				int nurPort = 4333;

				publishMessage("\nConnecting to : " + nurDevice + "\n", topicev);
				try 
				{
					NurApiSocketTransport socket = new NurApiSocketTransport(nurDevice, nurPort);
					mApi.setTransport(socket);
					mApi.connect();
				} 
				catch (Exception e) {
					
					if(e.getMessage().equals("Port in use.")) {
						publishMessage("Sorry! Port is in use!", topicev);
					}
					else {
						e.printStackTrace();
					}
					
					try {
						mApi.disconnect();	
					} catch (Exception e1) {
						e1.printStackTrace();
					}
					finally {
						cleanUp();
						System.exit(1);
					}
				}

				System.out.println("javasample_ar8x main leave");
				
	}
}
