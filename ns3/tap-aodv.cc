/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 IITP RAS
 *
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
 *
 * This is an example script for AODV manet routing protocol.
 *
 * Authors: Pavel Boyko <boyko@iitp.ru>
 */

#include "ns3/aodv-module.h"
#include "ns3/core-module.h"
// #include "ns3/common-module.h"
// #include "ns3/node-module.h"
// #include "ns3/helper-module.h"
#include "ns3/mobility-module.h"
// #include "ns3/contrib-module.h"
#include "ns3/wifi-module.h"
#include "ns3/v4ping-helper.h"
#include <iostream>
#include <cmath>

using namespace ns3;

/**
 * \brief Test script.
 *
 * This script creates 1-dimensional grid topology and then ping last node from the first one:
 *
 * [10.0.0.1] <-- step --> [10.0.0.2] <-- step --> [10.0.0.3] <-- step --> [10.0.04]
 *
 * ping 10.0.0.4
 */

#define COUNT 16
class AodvExample
{
public:
  AodvExample();
  /// Configure script parameters, \return true on successful configuration
  bool Configure(int argc, char **argv);
  /// Run simulation
  void Run();
  /// Report results
  void Report(std::ostream &os);

private:
  ///\name parameters
  //\{
  /// Number of nodes
  uint32_t size;
  /// Distance between nodes, meters
  double step;
  /// Simulation time, seconds
  double totalTime;
  /// Write per-device PCAP traces if true
  bool pcap;
  //\}

  // For Tap bridges
private:
  std::string tapNames[COUNT];
  std::string mappedMac[COUNT];
  std::string tapIps[COUNT];
  TapBridgeHelper tapBridge;
  std::string mode;
  std::string dummyIp;

  ///\name network
  //\{
  NodeContainer nodes;
  NetDeviceContainer devices;
  Ipv4InterfaceContainer interfaces;
  //\}

private:
  void CreateNodes();
  void CreateDevices();
  void InstallInternetStack();
  void InstallApplications();
  void InstallTapBridges(int index);
  void InstallTapBridges();
};

int main(int argc, char **argv)
{
  AodvExample test;
  if (!test.Configure(argc, argv))
    NS_FATAL_ERROR("Configuration failed. Aborted.");

  test.Run();
  test.Report(std::cout);
  return 0;
}

//-----------------------------------------------------------------------------
AodvExample::AodvExample() : size(COUNT),
                             step(80),
                             totalTime(6000),
                             pcap(true)
{
  //For bridged mode
  mode = "UseBridge";
  // For Tap name
  for (int i = 0; i < COUNT; i++)
  {
    std::ostringstream os;
    os << "tap10" << (i + 1);
    tapNames[i] = os.str();
  }
  // For Mac address. Now we only can do it mannually
  mappedMac[0] = "00:18:51:DB:1E:9C";
  mappedMac[1] = "00:18:51:20:FC:41";
  mappedMac[2] = "00:18:51:E2:34:B2",
  mappedMac[3] = "00:18:51:61:E1:F9",

  // For IP address, set it manually
      tapIps[0] = "10.1.1.101";
  tapIps[1] = "10.1.1.102";
  tapIps[2] = "10.1.1.103";
  tapIps[3] = "10.1.1.104";

  dummyIp = "10.1.1.200";
}

bool AodvExample::Configure(int argc, char **argv)
{
  // Enable AODV logs by default. Comment this if too noisy
  //LogComponentEnable("AodvRoutingProtocol", LOG_LEVEL_ALL);

  SeedManager::SetSeed(12345);
  CommandLine cmd;

  cmd.AddValue("pcap", "Write PCAP traces.", pcap);
  cmd.AddValue("size", "Number of nodes.", size);
  cmd.AddValue("time", "Simulation time, s.", totalTime);
  cmd.AddValue("step", "Grid step, m", step);

  cmd.Parse(argc, argv);
  return true;
}

void AodvExample::Run()
{
  //Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", UintegerValue (1)); // enable rts cts all the time.
  GlobalValue::Bind("SimulatorImplementationType", StringValue("ns3::RealtimeSimulatorImpl"));
  GlobalValue::Bind("ChecksumEnabled", BooleanValue(true));

  CreateNodes();
  CreateDevices();
  InstallInternetStack();
  //InstallApplications ();
  InstallTapBridges();
  //InstallTapBridges(1);

  std::cout << "Starting simulation for " << totalTime << " s ...\n";

  Simulator::Stop(Seconds(totalTime));
  Simulator::Run();
  Simulator::Destroy();
}

void AodvExample::Report(std::ostream &)
{
}

void AodvExample::CreateNodes()
{
  std::cout << "Creating " << (unsigned)size << " nodes " << step << " m apart.\n";
  nodes.Create(size);
  // Name nodes
  for (uint32_t i = 0; i < size; ++i)
  {
    std::ostringstream os;
    os << "node-" << i;
    Names::Add(os.str(), nodes.Get(i));
  }
  // Create static grid
  MobilityHelper mobility;
  mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                "MinX", DoubleValue(0.0),
                                "MinY", DoubleValue(0.0),
                                "DeltaX", DoubleValue(step),
                                "DeltaY", DoubleValue(step),
                                "GridWidth", UintegerValue(size / 4),
                                "LayoutType", StringValue("RowFirst"));
  mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
  mobility.Install(nodes);
}

void AodvExample::CreateDevices()
{
  NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default();
  wifiMac.SetType("ns3::AdhocWifiMac");
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default();
  YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
  wifiPhy.SetChannel(wifiChannel.Create());
  WifiHelper wifi = WifiHelper::Default();
  wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode", StringValue("wifia-6mbs"), "RtsCtsThreshold", UintegerValue(0));
  devices = wifi.Install(wifiPhy, wifiMac, nodes);

  if (pcap)
  {
    wifiPhy.EnablePcapAll(std::string("tap-aodv"));
  }
}

void AodvExample::InstallInternetStack()
{
  AodvHelper aodv;
  // you can configure AODV attributes here using aodv.Set(name, value)
  InternetStackHelper stack;
  stack.SetRoutingHelper(aodv);
  stack.Install(nodes);
  Ipv4AddressHelper address;
  address.SetBase("10.1.1.0", "255.255.255.0");
  interfaces = address.Assign(devices);
}

void AodvExample::InstallApplications()
{
  V4PingHelper ping(interfaces.GetAddress(size - 1));
  ping.SetAttribute("Verbose", BooleanValue(true));

  ApplicationContainer p = ping.Install(nodes.Get(0));
  p.Start(Seconds(0));
  p.Stop(Seconds(10) - Seconds(0.001));

  // move node away
  // get the middle node to move
  Ptr<Node> node = nodes.Get(size / 2);
  Ptr<MobilityModel> mob = node->GetObject<MobilityModel>();
  Simulator::Schedule(Seconds(totalTime / 3), &MobilityModel::SetPosition, mob, Vector(1e5, 1e5, 1e5));
}

void AodvExample::InstallTapBridges(int index)
{
  int nodeIndex;
  switch (index)
  {
  case 0:
    nodeIndex = 0;
    break;
  case 1:
    nodeIndex = size - 1;
    break;
  }
  //tapBridges[index] = TapBridgeHelper(interfaces.GetAddress(nodeIndex));
  tapBridge = TapBridgeHelper();
  tapBridge.SetAttribute("Mode", StringValue(mode));
  tapBridge.SetAttribute("DeviceName", StringValue(tapNames[index]));
  // Add the Mac address of Tap device
  tapBridge.SetAttribute("MacAddress", Mac48AddressValue(Mac48Address(mappedMac[index].c_str())));
  // Add the Ip address of Tap device
  tapBridge.SetAttribute("IpAddress", Ipv4AddressValue(Ipv4Address(tapIps[index].c_str())));
  // Set the IP address of virtual multicast
  //tapBridge.SetAttribute("DummyIP", Ipv4AddressValue(Ipv4Address(dummyIp.c_str())));

  tapBridge.Install(nodes.Get(nodeIndex), devices.Get(nodeIndex));
}

void AodvExample::InstallTapBridges()
{
  //tapBridges[index] = TapBridgeHelper(interfaces.GetAddress(nodeIndex));
  tapBridge = TapBridgeHelper();
  tapBridge.SetAttribute("Mode", StringValue(mode));
  int nodeindex = 0;
  for (int i = 0; i < 4; i++)
  {
    tapBridge.SetAttribute("DeviceName", StringValue(tapNames[i]));
    // Add the Mac address of Tap device
    tapBridge.SetAttribute("MacAddress", Mac48AddressValue(Mac48Address(mappedMac[i].c_str())));
    // Add the Ip address of Tap device
    tapBridge.SetAttribute("IpAddress", Ipv4AddressValue(Ipv4Address(tapIps[i].c_str())));
    // Set the IP address of virtual multicast
    //tapBridge.SetAttribute("DummyIP", Ipv4AddressValue(Ipv4Address(dummyIp.c_str())));

    switch (i)
    {
    case 0:
      nodeindex = 0;
      break;
    case 1:
      nodeindex = 3;
      break;
    case 2:
      nodeindex = 12;
      break;
    case 3:
      nodeindex = 15;
      break;
    }
    tapBridge.Install(nodes.Get(nodeindex), devices.Get(nodeindex));
  }
}
