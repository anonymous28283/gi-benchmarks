

return function(
	women,
	men
)

	local women_ranks = {}
	for woman, prefs in pairs(women) do
		women_ranks[woman] = {}
		for rank, man in ipairs(prefs) do
			women_ranks[woman][man] = rank
		end
	end

	local free_men = {}
	local men_rank = {}
	for man in pairs(men) do
		table.insert(free_men, man)
		men_rank[man] = 0
	end

	local elopements = {}
	while #free_men > 0 do
		local man = table.remove(free_men)
		men_rank[man] = men_rank[man] + 1
		local woman = men[man][men_rank[man]]
		local woman_ranks = women_ranks[woman]
		local cur_fiance = elopements[woman]
		if woman_ranks[man] < (woman_ranks[cur_fiance] or math.huge) then
			table.insert(free_men, cur_fiance)
			elopements[woman] = man
		else
			table.insert(free_men, man)
		end
	end
	return elopements
end
