# Test script for loading sequence data and extract stats from it.
# This should later be moved into python/app and python/test when I get a sample
# of how to hook the python in CMakefiles
#
import rocs.data.databases.COLD as COLD
import rocs.data.databases.VPC as VPC

def testCOLD():
  seq = COLD.COLDSequence('../../../data/samples/COLD/freiburg/seq1_cloudy1')
  
  categories = seq.category.keys()
  for cat1 in categories:
    for cat2 in categories:
      print "%s->%s => %d" % (cat1, cat2, seq.NumberOfEdgesBetweenCategories(cat1, cat2))

def testVPC():
  seq = VPC.VPCSequence('../../../data/samples/VPC/Home1')
  print list(seq.iterSamples())
  categories = seq.category.keys()
  for cat1 in categories:
    for cat2 in categories:
      if seq.HasCategoryEdge(cat1, cat2):
        print "%s->%s => connection" % (cat1, cat2)



testVPC()
