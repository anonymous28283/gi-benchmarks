







namespace greedy_algorithms {

namespace stable_matching {

std::vector<std::uint32_t> gale_shapley(
    const std::vector<std::vector<std::uint32_t>>& secondary_preferences,
    const std::vector<std::vector<std::uint32_t>>& primary_preferences) {
    std::uint32_t num_elements = secondary_preferences.size();
    std::vector<std::uint32_t> matches(num_elements, -1);
    std::vector<bool> is_free_primary(num_elements, true);
    std::vector<std::uint32_t> proposal_index(
        num_elements,
        0);

    while (true) {
        int free_primary_index = -1;


        for (std::uint32_t i = 0; i < num_elements; i++) {
            if (is_free_primary[i]) {
                free_primary_index = i;
                break;
            }
        }


        if (free_primary_index == -1)
            break;


        std::uint32_t secondary_to_propose =
            primary_preferences[free_primary_index]
                               [proposal_index[free_primary_index]];
        proposal_index[free_primary_index]++;


        std::uint32_t current_match = matches[secondary_to_propose];


        if (current_match == -1) {
            matches[secondary_to_propose] = free_primary_index;
            is_free_primary[free_primary_index] = false;
        } else {

            auto new_proposer_rank =
                std::find(secondary_preferences[secondary_to_propose].begin(),
                          secondary_preferences[secondary_to_propose].end(),
                          free_primary_index);
            auto current_match_rank =
                std::find(secondary_preferences[secondary_to_propose].begin(),
                          secondary_preferences[secondary_to_propose].end(),
                          current_match);


            if (new_proposer_rank < current_match_rank) {
                matches[secondary_to_propose] = free_primary_index;
                is_free_primary[free_primary_index] = false;
                is_free_primary[current_match] =
                    true;
            }
        }
    }

    return matches;
}
}
}


static void tests() {

    std::vector<std::vector<std::uint32_t>> primary_preferences = {
        {0, 1, 2, 3}, {2, 1, 3, 0}, {1, 2, 0, 3}, {3, 0, 1, 2}};
    std::vector<std::vector<std::uint32_t>> secondary_preferences = {
        {1, 0, 2, 3}, {3, 0, 1, 2}, {0, 2, 1, 3}, {1, 2, 0, 3}};
    assert(greedy_algorithms::stable_matching::gale_shapley(
               secondary_preferences, primary_preferences) ==
           std::vector<std::uint32_t>({0, 2, 1, 3}));


    primary_preferences = {
        {0, 2, 1, 3}, {2, 3, 0, 1}, {3, 1, 2, 0}, {2, 1, 0, 3}};
    secondary_preferences = {
        {1, 0, 2, 3}, {3, 0, 1, 2}, {0, 2, 1, 3}, {1, 2, 0, 3}};
    assert(greedy_algorithms::stable_matching::gale_shapley(
               secondary_preferences, primary_preferences) ==
           std::vector<std::uint32_t>({0, 3, 1, 2}));


    primary_preferences = {{0, 1, 2}, {2, 1, 0}, {1, 2, 0}};
    secondary_preferences = {{1, 0, 2}, {2, 0, 1}, {0, 2, 1}};
    assert(greedy_algorithms::stable_matching::gale_shapley(
               secondary_preferences, primary_preferences) ==
           std::vector<std::uint32_t>({0, 2, 1}));


    primary_preferences = {};
    secondary_preferences = {};
    assert(greedy_algorithms::stable_matching::gale_shapley(
               secondary_preferences, primary_preferences) ==
           std::vector<std::uint32_t>({}));
}


int main() {
    tests();
    return 0;
}
