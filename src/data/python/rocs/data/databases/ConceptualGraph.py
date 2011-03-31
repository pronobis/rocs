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
import rocs.data.conceptual as conceptual

class FactorGraph:
  def __init__(self, input):
    num_factors = int(next(input))
    self.factors = {}
    for f in range(num_factors):
      assert next(input).rstrip('\n') == ""
      num_vars = int(next(input))
      var_ids = map(int, next(input).split())
      var_sizes = map(int, next(input).split())
      potential = {}
      potentials = int(next(input))
      unwrap = self.UnwrapPotential(var_sizes)
      for p in range(potentials):
        [pid, pval] = next(input).split()
        pid  = int(pid)
        pval = float(pval)
        potential[unwrap(pid)] = pval
      self.factors[f] = {'vars': zip(var_ids, var_sizes), 'potential': potential}
  
  def UnwrapPotential(self, var_sizes):
    def Unwrap(pid):
      out = []
      for sz in var_sizes:
        out.append(pid % sz)
        pid /= sz
      return tuple(out)
    return Unwrap


class Info():
  def __init__(self, input):
    self.varName = {}
    self.varType = {}
    self.factorName = {}
    self.varValue = {}
    for line in input:
      line = line.rstrip('\n')
      if line == '': continue
      
      [obj, name] = line.split()
      if obj[0] == 'x':
        '''Reading a variable'''
        vid = int(obj[1:])
        self.varName[vid] = name
        self.varType[vid] = self.GuessVarType(name)
        self.varValue[vid] = {}
        while True:
          line = next(input).rstrip()
          if line == "": break
          [valueid, value] = line.split()
          self.varValue[vid][int(valueid)] = value
      else:
        assert obj[0] == 'f', 'Wrong format?'
        '''Reading a factor'''
        self.factorName[int(obj[1:])] = name
  
  def GuessVarType(self, varname):
    return re.sub('[0-9]+', '', varname)
  
def LoadConceptualGraph(path):
  fg = FactorGraph(open(os.path.join(path, 'conceptual.fg'), 'r'))
  info = Info(open(os.path.join(path, 'conceptual.info'), 'r'))
  
  m = conceptual.Graph()
  for var in info.varName:
    node = m.AddNode(info.varName[var], info.varType[var])
    node.values = info.varValue[var]
  for fac in fg.factors:
    vids,vsizes = zip(*fg.factors[fac]['vars'])
    for (vid, vsize) in fg.factors[fac]['vars']:
      assert  vsize == len(info.varValue[int(vid)])

    f = m.AddEdge("f%d" % fac, info.factorName[fac],
                  list(info.varName[int(vid)] for vid in vids))

    f.potential = {}
    for pindex, pval in fg.factors[fac]['potential'].items():
      pi = []
      for vid,vval in zip(vids, pindex): pi.append(info.varValue[vid][vval])
      f.potential[tuple(pi)] = pval

  return m


def LoadSequences(paths=glob.glob('../../../data/samples/ConceptualGraph/*')):
  for path in paths:
    yield LoadConcetualGraph(path)

