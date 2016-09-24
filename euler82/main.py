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
    v.up = vmat[ row+1][col]
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

def traverse( vertex, vmat, record):
  if record is None:
    record = [ (vertex.row, vertex.col)]
  print(record)

read = None
with open( "p082_matrix.small.txt") as f:
  matrix = parse( f)
  print( matrix)
  vmatrix = setVertexMatrix( matrix, None)

  print( matrix[1][0])
  minval = traverse(vmatrix[1][0], vmatrix, None)
#  minval = traverse( vmatrix[
#print( vmatrix)
