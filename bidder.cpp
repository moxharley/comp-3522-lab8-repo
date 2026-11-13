#include "bidder.hpp"
#include "auctioneer.hpp"
#include <cstdlib>

double ROLLED_MIN = 0;
double ROLLED_MAX = 1;

void Bidder::update(Auctioneer *auctioneer) {
    double f = (double)rand() / RAND_MAX;
    double random_chance = ROLLED_MIN + f * (ROLLED_MAX - ROLLED_MIN);
    double new_bid = auctioneer->get_highest_bid() * bid_increase_perc;
    if (new_bid < budget && random_chance < bid_probability) {
        highest_bid = new_bid;
        auctioneer->accept_bid(new_bid, this);
    }
}
