local floor = math.floor


return function(

	year,

	month,

	day_of_month
)

	if month <= 2 then
		year = year - 1
		month = month + 12
	end

	local day_of_week = (
		day_of_month
		+ floor(13 / 5 * (month + 1))
		+ year
		+ floor(year / 4)
		- floor(year / 100)
		+ floor(year / 400)
	) % 7
	if day_of_week == 0 then
		day_of_week = 7
	end
	return day_of_week
end
