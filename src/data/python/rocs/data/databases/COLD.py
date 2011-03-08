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
# This module allows using data from a COLD sequence.
# COLD sequences are found on: COLD/lab/sequence-name/localization/places.lst
# http://cogvis.nada.kth.se/COLD/
#
import re
import glob
from rocs.data.Sequence import Sequence, Sample

class COLDSequence(Sequence):
  def __init__(self, sequence_path):
    Sequence.__init__(self)
    self.path = sequence_path
    self.BuildFromTimeSequenceSamples(self.iterSamples())
  
  def iterSamples(self):
    placefile = open(self.path + '/localization/places.lst', 'r')
    for line in placefile:
        line = line.rstrip()
        (image, roomname) = line.rsplit(' ', 1)
        yield Sample(sequence = self,
                     std_cam  = self.path + '/std_cam/' + image,
                     roomname = roomname,
                     roomcategory = GuessRoomCategory(roomname))


# COLD only stores room names.
# From it its possible to derive the room category. 
def GuessRoomCategory(roomname):
  # List of used COLD abrevs.
  roomcategory_map = {
    'CR': 'Corridor',
    'TL': 'Toilet',
    'PA': 'PrinterArea',
    '2PO': 'TwoPersonOffice',
    '1PO': 'OnePersonOffice',
    'ST' : 'Stairs',
    'KT' : 'Kitchen',
    'LO' : 'LargeOffice',
    'LAB': 'Lab',
    'TR':  'TerminalRoom',
    'RL': 'RoboticLab',
    'CNR': 'ConferenceRoom'
  }
  # removes room -A suffix (COLD uses this)
  roomname = re.sub( '-[A-Z]$', '', roomname)
  # Removes room numeration
  roomname = re.sub( '\d+$', '', roomname)
  # Check map for existing know maps
  if roomname in roomcategory_map:
      roomname = roomcategory_map[roomname]
  return roomname

def LoadSequences(paths=glob.glob('../../../data/samples/COLD/*/*')):
  for path in paths:
    yield COLDSequence(path)

