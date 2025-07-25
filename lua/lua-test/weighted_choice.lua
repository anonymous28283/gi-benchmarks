local binary_search = require("searches.binary_search")

return function(
	weights
)

	local val_upper_bounds = {}
	local sum = 0
	for index, weight in pairs(weights) do
		sum = sum + weight
		val_upper_bounds[index] = sum
	end

	for index, val_upper_bound in pairs(val_upper_bounds) do
		val_upper_bounds[index] = val_upper_bound / sum
	end

	return function()

		return math.abs(binary_search(val_upper_bounds, math.random()))
	end
end
