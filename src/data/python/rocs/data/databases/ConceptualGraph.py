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
# This module allows using factor graphs dumped by dora conceptual module.
# Two files are needed: conceptual.fg, conceptual.info
#
import re
import os
import glob
from rocs.data.Sequence import Sequence, Sample

class FactorGraph:
  def __init__(self, input):
    num_factors = int(next(input))
    self.factors = {}
    for f in range(num_factors):
      assert next(input).rstrip('\n') == ""
      num_vars = int(next(input))
      var_ids = next(input).split()
      var_sizes = next(input).split()
      potential = {}
      potentials = int(next(input))
      for p in range(potentials):
        [pid, pval] = next(input).split()
        pid  = int(pid)
        pval = float(pval)
        potential[pid] = pval
      self.factors[f] = {'vars': zip(var_ids, var_sizes), 'potential': potential}

class ConceptualGraph(Sequence):
  def __init__(self, sequence_path):
    Sequence.__init__(self)
    self.path = sequence_path

    """Load Factor Graph as printed by libDAI"""
    self.loadFactorGraph(open(os.path.join(self.path, 'conceptual.fg'), 'r')) 

    """Load variables and factors names."""
    self.loadInfo(open(os.path.join(self.path, 'conceptual.info'), 'r'))
  
  def loadFactorGraph(self, input):
    self.factorGraph = FactorGraph(input)
  
  def loadInfo(self, input):
    self.varName = {}
    self.varType = {}
    self.factorName = {}
    for line in input:
      line = line.rstrip('\n')
      if line == '': continue

      [obj, name] = line.split()
      if obj[0] == 'x':
        '''Reading a variable'''
        self.varName[int(obj[1:])] = name
        self.varType[int(obj[1:])] = self.GuessVarType(name)
        while next(input).rstrip() != "": pass
      else:
        assert obj[0] == 'f', 'Wrong format?'
        '''Reading a factor'''
        self.factorName[int(obj[1:])] = name
    print self.varType

  def GuessVarType(self, varname):
    return re.sub('[0-9]+', '', varname)

  def IterVarsByType(self, vartype):
    return (x for x in self.varType if self.varType[x] == vartype)
  
  def IterRooms(self):
    return self.IterVarsByType('room_category')
  

def LoadSequences(paths=glob.glob('../../../data/samples/ConceptualGraph/*')):
  for path in paths:
    yield ConcetualGraph(path)

