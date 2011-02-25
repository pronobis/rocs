# -*- coding: utf-8 -*-
# ==================================================================
# ROCS - Toolkit for Robots Comprehending Space
# Copyright (C) 2011  André Susano Pinto
#
# This file is part of ROCS.
#
# ROCS is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3
# of the License, or (at your option) any later version.
#
# ROCS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ROCS. If not, see <http://www.gnu.org/licenses/>.
# ==================================================================

# This class contains data that represents a given sample of a sequence.
# Example all data associated with a given time.
class Sample:
  def __init__(self, sequence = None,
                     std_cam  = None,
                     roomname = None,
                     roomcategory = None):
    self.sequence = sequence
    self.std_cam = std_cam
    self.roomname = roomname
    self.roomcategory = roomcategory


# Sequence represents a sample of a recorded sequence.
# It allows to iterate over time in the sample and access variables on it.
class Sequence:
  def __init__(self):
    self.room_samples  = dict()
    self.room_edges    = set()
    self.category      = dict()
    self.category_edge = dict()
  
  def iterSamples(self):
    raise 'Not implemented'
  
  #################################################
  # The methods below are used to build statistics.
  #################################################
  def NumberOfRoomsInCategory(self, cat):
    if cat in self.category:
      return len(self.category[cat])
    else:
      return 0
  
  # Order dependent. It is build from room edges.
  # If edges are symmetric this will also be.
  def NumberOfEdgesBetweenCategories(self, cat1, cat2):
    key = (cat1, cat2)
    if key in self.category_edge:
      return len(self.category_edge[key])
    else:
      return 0
  
  #######################################
  # The methods below are to access data.
  #######################################
  def GetRoomCategory(self, roomname):
    # Assume all the samples had the same room category.
    return self.room_samples[roomname][0].roomcategory
  
  #########################################################
  # The methods bellow are used by the class to index data.
  # They cache data for fast answering the needed queries.
  #########################################################
  def AddRoomSample(self, roomname, sample):
    if roomname not in self.room_samples:
      self.room_samples[roomname] = []
    self.room_samples[roomname].append(sample)
  
  # This creates a symmetric edge
  def AddRoomEdge(self, roomname1, roomname2):
    self.room_edges.add((roomname1, roomname2))
    self.room_edges.add((roomname2, roomname1))
  
  def BuildFromTimeSequenceSamples(self, samples):
    prev = None
    for x in samples:
      # Builds reverse indexs to access room.
      self.AddRoomSample(x.roomname, x)
      
      # Detects room transitions
      if prev and x.roomname <> prev.roomname:
        self.AddRoomEdge(prev.roomname, x.roomname)
      prev = x
    
    # Build extra data structure to access by categories.
    self.BuildData()
  
  # Build data structures for querying room categories.
  # Assuming room and room edges are filled in.
  def BuildData(self):
    for roomname in self.room_samples.keys():
      cat = self.GetRoomCategory(roomname)
      if cat not in self.category:
        self.category[cat] = set()
      self.category[cat].add(roomname)
    
    for (room1, room2) in self.room_edges:
      cat1 = self.GetRoomCategory(room1)
      cat2 = self.GetRoomCategory(room2)
      key = (cat1, cat2)
      if key not in self.category_edge:
        self.category_edge[key] = set()
      self.category_edge[key].add((room1,room2))

