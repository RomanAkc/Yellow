//#pragma once
#include "Structs.h"
#include <vector>

#include <algorithm>
int FindMaxRepetitionCount(const std::vector<Region>& regions)
{
	struct Less
	{
		bool operator()(const Region* lhs, const Region* rhs) const
		{
			if (lhs->population != rhs->population)
				return lhs->population < rhs->population;

			if (lhs->std_name != rhs->std_name)
				return lhs->std_name < rhs->std_name;

			if (lhs->parent_std_name != rhs->parent_std_name)
				return lhs->parent_std_name < rhs->parent_std_name;

			return lhs->names < rhs->names;
		}
	};

	struct Equal
	{
		bool operator()(const Region* lhs, const Region* rhs) const
		{
			return
				lhs->population == rhs->population
				&& lhs->std_name == rhs->std_name
				&& lhs->parent_std_name == rhs->parent_std_name
				&& lhs->names == rhs->names;
		}
	};

	std::vector<const Region*> newRegions;

	for(auto&& obj : regions)
		newRegions.push_back(&obj);

	std::sort(newRegions.begin(), newRegions.end(), Less());

	size_t max = 0;
	size_t count = 0;
	const Region* pPrevRegion = nullptr;

	for (auto pRegion : newRegions)
	{
		if (!pPrevRegion)
		{
			pPrevRegion = pRegion;
			count++;
			continue;
		}
			
		if(Equal()(pRegion, pPrevRegion))
			count++;
		else
		{
			if (count > max)
				max = count;
			count = 1;
		}

		pPrevRegion = pRegion;
	}

	if (count > max)
		max = count;

	return static_cast<int>(max);
}