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
#
# This module allows using data from a VPC sequence.
# http://categorizingplaces.com/dataset.html
#
# VPC sequences are identified with url to: VPC/<home>
# Sequence data is then read from <path>/label.txt
#
# Since VPC does not provides data about the room, its impossible to know
# if the same room is visting twice or are diferent instances of a given category.
# For that reason functions as NumberOfEdges and NumberOfRooms are disabled.
import re
from rocs.data.Sequence import Sequence, Sample

class VPCSequence(Sequence):
  def __init__(self, sequence_path):
    Sequence.__init__(self)
    self.path = sequence_path
    self.BuildData()
  
  def NumberOfRoomsInCategory(self, cat):
    raise 'Not implemented'
  
  # Order dependent. It is build from room edges.
  # If edges are symmetric this will also be.
  def NumberOfEdgesBetweenCategories(self, cat1, cat2):
    raise 'Not implemented'
  
  def BuildData(self):
    last_cat = None
    for (lower, upper, cat, path) in self._iterLabels():
      if cat == 'End':
        last_cat = None
        continue
      if cat == 'Transition':
        continue
      
      if cat not in self.category:
        self.category[cat] = []
      if last_cat and last_cat <> cat:
        key = (last_cat, cat)
        if key not in self.category_edge:
          self.category_edge[key] = set()
      last_cat = cat
  
  def _iterLabels(self):
    current_path = self.path+'/'
    labelfile = open(self.path + '/label.txt', 'r')
    for line in labelfile:
      line = line.strip()
      match = re.match('('
        '(?P<path>\w+\/)|'
        '(?P<number>\d+)|'
        '(?P<start_frame>-?\d+)\s+(?P<end_frame>-?\d+)\s+(?P<category>\w+))$',
        line)
      if not match:
        print 'VPC load(%s): Skiping line: %s' % (self.path, line)
        continue
      if match.group('path'):
        current_path = self.path+'/' + match.group('path')
      elif match.group('number'):
        # ignore the line with the number of frames
        continue
      elif match.group('start_frame'):
        lower = int(match.group('start_frame'))
        upper = int(match.group('end_frame'))
        categ = CanonizeRoomCategory(match.group('category'))
        yield (lower, upper, categ, current_path)
  
  def iterSamples(self):
    for (lower, upper, categ, path) in self._iterLabels():
      if lower == -1:
        continue
      for frame in range(lower, upper+1):
        yield Sample(sequence = self,
                     std_cam  = '%s/%08d.jpg' % (path, frame),
                     roomcategory = categ)


# VPC uses lower case and underscore separated categories.
# Convert it to camel case and fix any special naming scheme.
def CanonizeRoomCategory(roomcat):
    # Capitalize and remove underscores
    roomname = ''.join( s.capitalize() for s in roomcat.split('_'))
    # List of used VPC abrevs.
    roomcategory_map = {
        'Bathroom' : 'Toilet'
    }
    # Check map for existing know maps
    if roomname in roomcategory_map:
        roomname = roomcategory_map[roomname]
    return roomname
