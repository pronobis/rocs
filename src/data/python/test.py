# Test script for loading sequence data and extract stats from it.
# This should later be moved into python/app and python/test when I get a sample
# of how to hook the python in CMakefiles
#
import rocs.data.databases.COLD as COLD

seq = COLD.COLDSequence('../../../data/samples/COLD/freiburg/seq1_cloudy1')

categories = seq.category.keys()
for cat1 in categories:
  for cat2 in categories:
    print "%s->%s => %d" % (cat1, cat2, seq.NumberOfEdgesBetweenCategories(cat1, cat2))

