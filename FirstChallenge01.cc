    #include "ns3/core-module.h"
    #include "ns3/network-module.h"
    #include "ns3/internet-module.h"
    #include "ns3/point-to-point-module.h"
    #include "ns3/applications-module.h"
    
    using namespace ns3;
    
    NS_LOG_COMPONENT_DEFINE ("FirstChallenge01");
    
    int
    main (int argc, char *argv[])
    {
      Time::SetResolution (Time::NS);
      LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
      LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
    
      NodeContainer nodes;
      nodes.Create (2);
    
      PointToPointHelper pointToPoint;
      pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
      pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
    
      NetDeviceContainer devices;
      devices = pointToPoint.Install (nodes);
    
      InternetStackHelper stack;
      stack.Install (nodes);
    
      Ipv4AddressHelper address;
      address.SetBase ("10.1.1.0", "255.255.255.0");
    
      Ipv4InterfaceContainer interfaces = address.Assign (devices);
      
      // application

	// primeiro pacote

      UdpEchoServerHelper echoServer (9);
    
      ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
      serverApps.Start (Seconds (1.0));
      serverApps.Stop (Seconds (20.0)); // finalizando aos 20 segundos
    
      UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
      echoClient.SetAttribute ("MaxPackets", UintegerValue (1)); 
      echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0))); 
      echoClient.SetAttribute ("PacketSize", UintegerValue (1024)); // tamanho padrão
    
      ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
      clientApps.Start (Seconds (2.0));
      clientApps.Stop (Seconds (20.0)); // finalizando aos 20 segundos
    
	// segundo pacote      

      UdpEchoClientHelper echoClient2 (interfaces.GetAddress (1), 9);
      echoClient2.SetAttribute ("MaxPackets", UintegerValue (1)); 
      echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0))); 
      echoClient2.SetAttribute ("PacketSize", UintegerValue (2048)); // dobro do tamanho do primeiro pacote
    
      ApplicationContainer clientApps2 = echoClient2.Install (nodes.Get (0));
      clientApps2.Start (Seconds (6.0));
      clientApps2.Stop (Seconds (20.0)); // finalizando aos 20 segundos
    

      Simulator::Run ();
      Simulator::Destroy ();
      return 0;
    }
