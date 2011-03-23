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

# This class represents a conceptual map.
#
# ConceptualMaps can be created from dumps of the conceptual modules or from
# other database sequences.
#

class Graph:
  def __init__(self):
    self.node = {}
    self.edge = {}
  
  def AddNode(self, name, type):
    assert name not in self.node
    node = ConceptualNode(name, type)
    self.node[name] = node
    return node
  
  def AddEdge(self, name, type, nodes):
    assert name not in self.edge
    for node in nodes: assert node in self.node
    
    edge = ConceptualEdge(name, type, nodes)
    self.edge[name] = edge
    for node in nodes:
      self.node[node].edge.append(edge)
    return edge
  
  
  def ListNodesByType(self, type):
    for node in self.nodes:
      if node.type == type:
        yield node
  
  def ListEdgesByType(self, type):
    for edge in self.edges:
      if edge.type == type:
        yield edge
  
  def SaveAsDot(self, f):
    f.write("graph FactorGraph { overlap=scalexy; splines=true;\n")
    f.write("node[shape=ellipse];\n")
    for node in self.node: print("  %s;"%node)
    f.write("node[shape=box];\n")
    for edge in self.edge: print("  %s;"%edge)
    for edge in self.edge:
      for node in self.edge[edge].nodes:
        f.write("  %s -- %s;\n" % (edge, node))
    f.write("}\n")


class ConceptualNode:
  """Represents a given instance of a concept.
     Example: A room_category."""
  def __init__(self, name, type):
    self.name = name
    self.type = type
    self.edge = []

class ConceptualEdge:
  """Represents a given factor/edge between nodes."""
  def __init__(self, name, type, nodes):
    self.name = name
    self.type = type
    self.nodes = nodes

