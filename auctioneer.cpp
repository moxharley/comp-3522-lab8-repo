#include "auctioneer.hpp"

void Auctioneer::register_bidder(Bidder *bidder) {
    // TODO: add bidder to the bidders vector.
}

void Auctioneer::reset_auctioneer() {
    // TODO: clear the bidders vector and reset highest_bid/highest_bidder.
}

void Auctioneer::notify_bidders() {
    // TODO: call update(this) on every registered bidder except
    // highest_bidder (a bidder cannot retaliate to their own bid).
}

void Auctioneer::accept_bid(double bid, Bidder *bidder) {
    // TODO: if bid > highest_bid, record the new highest_bid/highest_bidder
    // and call notify_bidders().
}
