local math = require( "math")

local primes = {}
function isprime( n)
	if (n <= 1) then return end
	if (n == 2) then return true end
	if( primes[n]) then return true end

	-- http://lua-users.org/wiki/SimpleRound
	local s = math.floor( math.sqrt(n) + 1 + 0.5 )

	while( s>1) do
		if( n%s == 0) then
			return 
		end
		s = s-1;
	end
	primes[ n] = true
	return true
end

local emap = {} -- exclude map
function excludes( p1, p2)
	if not p2 then
			return isprime(p1)
	end
	local p1p2 = tonumber( tostring( p1) .. tostring( p2))
	if not isprime( p1p2) then
		return
	end
	
	local p2p1 = tonumber( tostring( p2) .. tostring( p1))
	if not isprime( p2p1) then
		return
	end
	return true
end

-- main
local nums = {}
for _, v in pairs( arg) do
	table.insert( nums, tonumber( v))
end

local allprime = true
for i=1, #nums-1 do
	for j=i+1, #nums do
			if not excludes(nums[i], nums[j]) then
				allprime = false
				break
			end
		end
end

if allprime then
	print( "allprime true : ", table.concat( nums, " "))
else
	print( "allprime false")
end
