/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
    /*
     * This program is free software; you can redistribute it and/or modify
     * it under the terms of the GNU General Public License version 2 as
     * published by the Free Software Foundation;
     *
     * This program is distributed in the hope that it will be useful,
     * but WITHOUT ANY WARRANTY; without even the implied warranty of
     * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     * GNU General Public License for more details.
     *
     * You should have received a copy of the GNU General Public License
     * along with this program; if not, write to the Free Software
     * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
     */
    
    #include "ns3/core-module.h"
    #include "ns3/network-module.h"
    #include "ns3/csma-module.h"
    #include "ns3/internet-module.h"
    #include "ns3/point-to-point-module.h"
    #include "ns3/applications-module.h"
    #include "ns3/ipv4-global-routing-helper.h"
    
    // Default Network Topology
    //
    //       10.1.1.0
    // n0 -------------- n1   n2   n3   n4
    //    point-to-point  |    |    |    |
    //                    ================
    //                      LAN 10.1.2.0
    
    
    using namespace ns3;
    
    NS_LOG_COMPONENT_DEFINE ("SecondChallenge01");
    
    int 
    main (int argc, char *argv[])
    {
      bool verbose = true;
      uint32_t nCsma = 3;
    
      CommandLine cmd;
      cmd.AddValue ("nCsma", "Number of \"extra\" CSMA nodes/devices", nCsma);
      cmd.AddValue ("verbose", "Tell echo applications to log if true", verbose);
    
      cmd.Parse (argc,argv);
    
      if (verbose)
        {
          LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
          LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
        }
    
      nCsma = nCsma == 0 ? 1 : nCsma;
    
      NodeContainer p2pNodes;
      p2pNodes.Create (2);
    
      NodeContainer csmaNodes;
      csmaNodes.Add (p2pNodes.Get (1));
      csmaNodes.Create (nCsma);
    
      PointToPointHelper pointToPoint;
      pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
      pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
    
      NetDeviceContainer p2pDevices;
      p2pDevices = pointToPoint.Install (p2pNodes);
    
      CsmaHelper csma;
      csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
      csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));
    
      NetDeviceContainer csmaDevices;
      csmaDevices = csma.Install (csmaNodes);
    
      InternetStackHelper stack;
      stack.Install (p2pNodes.Get (0));
      stack.Install (csmaNodes);
    
      Ipv4AddressHelper address;
      address.SetBase ("10.1.1.0", "255.255.255.0");
      Ipv4InterfaceContainer p2pInterfaces;
      p2pInterfaces = address.Assign (p2pDevices);
    
      address.SetBase ("10.1.2.0", "255.255.255.0");
      Ipv4InterfaceContainer csmaInterfaces;
      csmaInterfaces = address.Assign (csmaDevices);
    
        // application 

      UdpEchoServerHelper echoServer (7); // modificando a porta do servidor
    
      ApplicationContainer serverApps = echoServer.Install (csmaNodes.Get (nCsma));
      serverApps.Start (Seconds (1.0));
      serverApps.Stop (Seconds (25.0)); // modificando o término da aplicação
    
      UdpEchoClientHelper echoClient (csmaInterfaces.GetAddress (nCsma), 7); // modificando a porta do servidor
      echoClient.SetAttribute ("MaxPackets", UintegerValue (2)); // modificando o número de pacotes
      echoClient.SetAttribute ("Interval", TimeValue (Seconds (6.0))); // modificando o intervalo entre os pacotes
      echoClient.SetAttribute ("PacketSize", UintegerValue (2048)); // modificando o tamanho dos pacotes
   
      ApplicationContainer clientApps = echoClient.Install (p2pNodes.Get (0));
      clientApps.Start (Seconds (2.0));
      clientApps.Stop (Seconds (25.0)); // modificando o término da aplicação
   
      Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
   
      pointToPoint.EnablePcapAll ("SecondChallenge01");
      csma.EnablePcap ("SecondChallenge01", csmaDevices.Get (1), true);
   
      Simulator::Run ();
      Simulator::Destroy ();
      return 0;
   }
