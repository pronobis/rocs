# Test script for loading sequence data and extract stats from it.
# This should later be moved into python/app and python/test when I get a sample
# of how to hook the python in CMakefiles
#
import rocs.data.databases.COLD as COLD
import rocs.data.databases.VPC as VPC
import rocs.data.databases.ConceptualGraph as CG

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

def testConceptualGraph():
  cg = CG.ConceptualGraph('../../../data/samples/ConceptualGraph/sample1')
  print(list(cg.IterRooms()))

testConceptualGraph()

sequences = list(COLD.LoadSequences()) # + list(VPC.LoadSequences())
room_cats = set(cat for seq in sequences for cat in seq.category.keys())

def SequencesWithConnection(a, b):
  return len([seq for seq in sequences if seq.HasCategoryEdge(a, b)])
    
def SequencesWithRooms(a, b):
  return len([seq for seq in sequences if a in seq.category and b in seq.category])

p_connection = dict()
for a in room_cats:
  for b in room_cats:
    numem = SequencesWithConnection(a, b)
    denom = SequencesWithRooms(a, b)
    p_connection[a, b] = numem/float(denom) if denom != 0 else 0

for item in sorted(p_connection.items()):
  print item
