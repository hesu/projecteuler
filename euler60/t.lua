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
	if not emap[p1] then emap[p1] = {} end
	if not emap[p2] then emap[p2] = {} end

	if emap[p1][p2] then
		if emap[p1][p2] == true then
			if not emap[p2][p1] then emap[p2][p1] = true end
--				print( "1) return")
			return true
		else
			if not emap[p2][p1] then emap[p2][p1] = false end
--				print( "2) return")
			return
		end
	end

	if emap[p2][p1] then
		if emap[p2][p1] == true then
			if not emap[p1][p2] then emap[p1][p2] = true end
--				print( "3) return")
			return true
		else
			if not emap[p1][p2] then emap[p1][p2] = false end
--				print( "4) return")
			return
		end
	end

	local p1p2 = tonumber( tostring( p1) .. tostring( p2))
	if not isprime( p1p2) then
		emap[p1][p2] = false
		emap[p2][p1] = false
--				print( "5) return")
		return
	end
	
	local p2p1 = tonumber( tostring( p2) .. tostring( p1))
	if not isprime( p2p1) then
		emap[p1][p2] = false
		emap[p2][p1] = false
--				print( "6) return")
		return
	end
		emap[p1][p2] = false
		emap[p2][p1] = false
--				print( "7) return")
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

local combination
combination = function( t, size, choose, nowi, r)
--	io.write( "comb() r: "); for k, v in ipairs( r) do io.write( v, " ") end; print("")
	if not r then r = {} end
	if (choose <= 0) or (nowi > #t) then
		-- DONE -- PRINT!
		if choose == 0 then
			io.write( "!!! Result r: "); for k, v in ipairs( r) do io.write( v, " ") end; print("")
		end
		table.remove( r, #r)
		----------------
		return
	end

	for i=nowi, #t do
		local keepgo = true
		for _, prime in pairs( r) do
			if not excludes( t[nowi], prime) then
				--print( "\t excludes true. keepgo = false. t[nowi]=", t[nowi], "prime=",prime, "i=", i)
				keepgo = false
				break
			end
		end

		if keepgo then
--			local newr = tcopy( r) 
			table.insert( r, t[nowi])
			combination( t, size, choose-1, i+1, r)
		else
			--io.write( "can't go. r: "); for k, v in ipairs( r) do io.write( v, " ") end; print("")
		end
	end

end

-- main --
local stime = os.time()

local t ={}
for i=2, 10000 do 
	if isprime(i) then table.insert( t, i) end
end

print( "primes=",#t)

for i, num in ipairs( t) do
	print( "combination at i=", i, "elapsed time=", os.time()-stime)
	local r = {}
	combination( t, #t, 5, i, r)
end

print( "done.elapsed time=",os.time()-stime)
