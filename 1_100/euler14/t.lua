
local t = {}


local collatz
collatz = function( n, i)
	if n == 1 then
		return i
	end

	local ne
	if n%2 == 0 then
		ne = n/2;		
	else
		ne = 3*n+1;
	end

	if t[ne] then
		return t[ne] + i
	end
	return collatz(ne, i+1);
end


local longest = 0
local whoproduces = nil

for i=1, 100*10000 do
	local co = collatz( i,0)
	print( "i=", i, "co=", co)
	if co and not t[i] then
		t[i] = co
	end

	if longest < co then
		longest = co
		whoproduces = i
	end
end

print( "longest=", longest, "who produces? =", whoproduces)
