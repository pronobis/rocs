# Test script for loading sequence data and extract stats from it.
# This should later be moved into python/app and python/test when I get a sample
# of how to hook the python in CMakefiles
#
import rocs.data.databases.COLD as COLD
import rocs.data.databases.VPC as VPC
import sys

def testCOLD():
  seq = COLD.COLDSequence('../../../data/samples/COLD/freiburg/seq1_cloudy1')
  
  categories = seq.category.keys()
  for cat1 in categories:
    for cat2 in categories:
      print "%s->%s => %d" % (cat1, cat2, seq.NumberOfEdgesBetweenCategories(cat1, cat2))

def testVPC():
  seq = VPC.VPCSequence('../../../data/samples/VPC/Home1')
  categories = seq.category.keys()
  for cat1 in categories:
    for cat2 in categories:
      if seq.HasCategoryEdge(cat1, cat2):
        print "%s->%s => connection" % (cat1, cat2)

COLD.COLDSequence('../../../data/samples/COLD/freiburg/seq1_cloudy1').ExtractConceptualGraph().SaveAsDot(sys.stdout)

sequences = list(COLD.LoadSequences()) # + list(VPC.LoadSequences())
room_cats = set(cat for seq in sequences for cat in seq.category.keys())

def SequencesWithConnection(a, b):
  return len([seq for seq in sequences if seq.HasCategoryEdge(a, b)])
    
def SequencesWithRooms(a, b):
  return len([seq for seq in sequences if a in seq.category and b in seq.category])

def print_room_category_connectivity():
  print('<room_category_connectivity>')
  print('  <item var="var1" type="room_category" />')
  print('  <item var="var2" type="room_category" />')
  
  for a in room_cats:
    for b in room_cats:
      numem = SequencesWithConnection(a, b)
      denom = SequencesWithRooms(a, b)
      potential = numem/float(denom) if denom != 0 else 0
      potential = numem
      print('  <item var1=%-20s var2=%-20s potential="%d" />' % ('"%s"'%a, '"%s"'%b, potential))
  print('</room_category_connectivity>')

