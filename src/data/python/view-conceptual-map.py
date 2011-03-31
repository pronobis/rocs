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
import rocs.data.databases.ConceptualGraph as CG
import sys

def SetFromObservedProperty(cg):
  for fname, f in cg.edge.items():
    if f.type.startswith('Observed') and len(f.nodes) == 1:
      ((p_argmax,), p_max) = max(f.potential.iteritems(), key=lambda x:x[1])
      cg.node[f.nodes[0]].observed_value = p_argmax
      f.dot_hide = True

if __name__ == "__main__":
  for path in sys.argv[1:]:
    cg = CG.LoadConceptualGraph(path)
    SetFromObservedProperty(cg)
    cg.SaveAsDot(sys.stdout)
