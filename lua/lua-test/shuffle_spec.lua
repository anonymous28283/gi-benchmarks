describe("Fisher-Yates shuffle", function()
	local shuffle = require("random.shuffle")
	local sums = {}
	local list = {}
	for i = 1, 10 do
		sums[i] = 0
		list[i] = i
	end

	for _ = 1, 1e5 do
		shuffle(list)

		for i, v in ipairs(list) do
			sums[i] = sums[i] + v
		end
	end

	assert.truthy(math.max(unpack(sums)) - math.min(unpack(sums)) <= 1e4, sums)
end)
