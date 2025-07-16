return function(
	height,
	move
)
	local function solve(left, from, spare, to)
		if left == 0 then
			return
		end
		solve(left - 1, from, to, spare)
		move(from, to)
		solve(left - 1, spare, from, to)
	end
	solve(height, 1, 2, 3)
end
