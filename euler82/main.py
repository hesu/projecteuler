import copy
import sys

size = 80
memo = [[None for i in range(size)] for j in range(size)]

class Vertex :
  def __init__(self, row=0, col=0, val=0) :
    self.row = row
    self.col = col
    self.val = val
    self.up = None
    self.down = None
    self.right = None

def parse(f):
  return[[ int(n) for n in row.split(',')] for row in f];

def setVertexNeighbor( vmat, row, col):
  v = vmat[row][col]
  if v.up is None and row > 0:
    v.up = vmat[ row-1][col]
  if v.down is None and row < len(vmat)-1:
    v.down = vmat[ row+1][col]
  if v.right is None and col < len(vmat)-1:
    v.right = vmat[ row][col+1]

def setVertexMatrix( mat, vmat):
  if vmat is None:
    vmat = [[None for i in range(len(mat))] for j in range(len(mat))]
  for row in range( len(mat)):
    for col in range( len(mat[row])):
      # if None then create!
      vmat[row][col] = Vertex( row, col, mat[row][col])
  
  for row in range( len(vmat)):
    for col in range( len(vmat[row])):
      setVertexNeighbor( vmat, row, col)
  
  return vmat

def traverse( vertex, vmat, record, traversum):
#  if memo[vertex.row][vertex.col] is not None :
#    return memo[vertex.row][vertex.col]

  if record is None:
    record = [ (vertex.row, vertex.col)]

  if vertex.right is None :
    # END condition
    return traversum + vmat[ vertex.row][vertex.col].val

  upval = sys.maxint
  if vertex.up is not None :
    if (vertex.row-1, vertex.col) not in record :
      ur = copy.deepcopy( record)
      ur.append( ( vertex.row, vertex.col))
      upval = traversum + traverse( vmat[ vertex.row-1][vertex.col], vmat, ur, vertex.val)

  downval = sys.maxint
  if vertex.down is not None :
    if (vertex.row+1, vertex.col) not in record :
      dr = copy.deepcopy( record)
      dr.append( (vertex.row, vertex.col))
      downval = traversum + traverse( vmat[ vertex.row+1][vertex.col], vmat, dr, vertex.val)
  
  rightval = sys.maxint
  if vertex.right is not None :
    rr = copy.deepcopy( record)
    rightval = traversum + traverse( vmat[ vertex.row][vertex.col+1], vmat, rr, vertex.val)

  print( "REACHED!!!!!", "row=", vertex.row, "col=", vertex.col)
  minval = min( upval, downval, rightval)
  
  if memo[vertex.row][vertex.col] is None :
    print( "memo. minval=", minval, "row=", vertex.row, "col=", vertex.col)
    memo[vertex.row][vertex.col] = minval

  return minval

print( sys.setrecursionlimit( 6500)) 
print( sys.getrecursionlimit()) 
with open( "p082_matrix.txt") as f:
#with open( "p082_matrix.small.txt") as f:
  matrix = parse( f)
#  print( matrix)
  vmatrix = setVertexMatrix( matrix, None)

  minvals = [] 
  for i in range( len(vmatrix)) :
    minvals.append( traverse( vmatrix[i][0], vmatrix, None, 0))
  
  print( "minval=", min(minvals))
#  minval = traverse( vmatrix[
#print( vmatrix)
