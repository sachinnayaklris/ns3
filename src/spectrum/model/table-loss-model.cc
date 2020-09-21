/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2020 University of Washington
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
 * Authors: Tom Henderson <tomh@tomh.org>
 *          Collin Brady <collinb@uw.edu>
 */

#include <ns3/mobility-model.h>
#include <ns3/table-loss-model.h>
#include <ns3/simulator.h>
#include <ns3/node.h>
#include <iostream>
#include <sstream>
#include <fstream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TableLossModel");

NS_OBJECT_ENSURE_REGISTERED (TableLossModel);


TableLossModel::TableLossModel ()
{
	NS_LOG_FUNCTION (this);
  	SetNext (NULL);
}

TableLossModel::~TableLossModel ()
{
}


TypeId
TableLossModel::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TableLossModel")
    .SetParent<SpectrumPropagationLossModel> ()
    .SetGroupName ("Spectrum")
    .AddConstructor<TableLossModel> ()
  ;
  return tid;
}

Ptr<SpectrumValue>
TableLossModel::DoCalcRxPowerSpectralDensity (Ptr<const SpectrumValue> txPsd,
                                                                 Ptr<const MobilityModel> a,
                                                                 Ptr<const MobilityModel> b) const
{

  Ptr<SpectrumValue> rxPsd = Copy<SpectrumValue> (txPsd);
  Values::iterator vit = rxPsd->ValuesBegin ();
  Bands::const_iterator fit = rxPsd->ConstBandsBegin ();

  NS_ASSERT (a);
  NS_ASSERT (b);


  // assume a is the eNb, b is the UE, on the DL
  uint32_t enbId = a->GetObject<Node> ()->GetId();
  uint32_t ueId = b->GetObject<Node> ()->GetId();
  uint32_t currentRb = 0;

  while (vit != rxPsd->ValuesEnd ())
    {
      NS_ASSERT (fit != rxPsd->ConstBandsEnd ());
      *vit = GetRxPsd (enbId, ueId, currentRb);
      ++vit;
      ++fit;
      ++currentRb;
    }
  return rxPsd;
}

#ifdef NOTYET
double
TableLossModel::GetRxPsd (uint32_t enbId, uint32_t ueId, uint32_t rbIndex) const
{
  
  // compute array index from 'now' which must be discretized to a 1us boundary
  uint64_t nowMs = Simulator::Now ().GetMilliSeconds ();
  // fetch and return value for (enbId, ueId, nowUs) from data structure
  return m_traceVals[enbId-1][ueId-1][rbIndex][nowMs-1]
}


void
TableLossModel::initializeTraceVals (uint32_t numEnbs, uint32_t numUes, uint32_t numRbs, uint32_t simSubFrames)
{
  
  m_numRb = numRbs;
  m_numEnb = numEnbs;
  m_numUe = numUes;
  m_numSubFrames = simSubFrames;
  
  
  m_traceVals.resize(numeNbs);
  for (int n = 0; n < numeNbs; ++n)
  {
    m_traceVals[n].resize(numUEs);
    for (int m = 0; m < numUEs; ++m)
    {
      m_traceVals[n][m].resize(numRbs);
      for (int r = 0; r < numRbs; ++r)
      {
        m_traceVals[n][m][r].resize(simSubFrames);
      }
    }
  }
}





void
TableLossModel::LoadTrace (std:string fileName)
{
  
  // get the identifiers from the filename
  // filename bust be formatted as such: 
  //SECTION NOT DONE 
  std::string fileName = "ULDL_Channel_Response_TX_1_Sector_1_UE_1_.txt";
  std::vector <std::string> tokens; 

  std::stringstream toParse(fileName); 
  std::string temp; 

  while(std::getline(toParse, temp, '_')) 
  { 
      tokens.push_back(temp); 
  } 

    
  int enbId = std::stoi(tokens[4]);
  int ueId  = std::stoi(tokens[8]);
  
  
  
  std::ifstream  data(fileName);
  std::string line;
  double val;

  for (int currentRb = 0; currentRb < m_numRb; ++currentRb)
  {
      std::getline(data,line);
      std::stringstream lineStream(line);
      for (int currentTimeIndex = 0; currentTimeIndex < m_numSubFrames; ++currentTimeIndex)
      {
          lineStream >> val;

          m_traceVals[m_numEnb-1][m_numUe-1][currentRb][currentTimeIndex] = val;

          if(lineStream.peek() == ' ') lineStream.ignore();

      }
  }
  
  
  
}
#endif

}  // namespace ns3
