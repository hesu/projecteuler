local math = require( "math")

local primes = {}
function isprime( n)
	if (n <= 1) then return end
	if (n == 2) then return true end
	if( primes[n]) then return true end

	local s = math.sqrt(n) + 1

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
	if not emap[p1] then emap[p1] = {} end
	if not emap[p2] then emap[p2] = {} end

	if emap[p1][p2] then
		if emap[p1][p2] == true then
			if not emap[p2][p1] then emap[p2][p1] = true end
			return true
		else
			if not emap[p2][p1] then emap[p2][p1] = false end
			return
		end
	end

	if emap[p2][p1] then
		if emap[p2][p1] == true then
			if not emap[p1][p2] then emap[p1][p2] = true end
			return true
		else
			if not emap[p1][p2] then emap[p1][p2] = false end
			return
		end
	end

	local p1p2 = tonumber( tostring( p1) .. tostring( p2))
	if not isprime( p1p2) then
		emap[p1][p2] = false
		emap[p2][p1] = false
		return
	end
	
	local p2p1 = tonumber( tostring( p2) .. tostring( p1))
	if not isprime( p2p1) then
		emap[p1][p2] = false
		emap[p2][p1] = false
		return
	end
		emap[p1][p2] = false
		emap[p2][p1] = false
	return true
end

function print_emap()
	for k, v in pairs( emap) do
		print( "p1=", k)
		for kk, vv in pairs( v) do
			print( "\tp2=", kk, vv)
		end
	end
end

local tcopy 
tcopy = function( o, seen)
    seen = seen or {}
    if not o then return nil end
    if seen[o] then return seen[o] end

    local no
    if type(o) == "table" then
        no = {}
        seen[o] = no

        for k, v in next, o, nil do
            no[ tcopy( k, seen)] = tcopy( v, seen)
        end
        setmetatable( no, tcopy( getmetatable( o), seen))
    else
        no = o
    end
    return no
end

-- TODO
local combination
combination = function( t, size, choose, nowi, r)
	if not r then r = {} end

	if (choose <= 0) or (nowi > #t) then
		-- DONE -- PRINT!
		io.write( "r: ")
		for k, v in pairs( r) do io.write( v, " ") end
		print("")
		----------------
		return
	end

	for i=nowi, #t do
		local keepgo = true
		for _, prime in pairs( r) do
			if excludes( t[nowi], prime) then
				keepgo = false
				break
			end
		end

		if keepgo then
			local newr = tcopy( r) 
			table.insert( r, t[nowi])
			combination( t, size, choose-1, i+1, newr)
		else
			print( "can't go. r[1]=", r[1])
		end
	end
end

local t ={ 2,3,5,7,11,13,17,19 }
local r = {}
combination( t, #t, 2, 1, r)

