#pragma once

#include <vector>
#include "bidder.hpp"

using namespace std;

/*
Auctioneer is the "subject" in our simplified observer pattern. It tracks
the current highest bid and bidder, and notifies every registered Bidder
(except whoever just bid) whenever a new, higher bid is accepted.
*/
class Auctioneer {
    vector<Bidder *> bidders;
    double highest_bid = 0;
    Bidder *highest_bidder = nullptr;

public:
    Auctioneer() = default;

    /*
    Adds a bidder to the list of tracked bidders.
    :param bidder: the Bidder to register.
    */
    void register_bidder(Bidder *bidder);

    /*
    Resets the auctioneer. Removes all the bidders and resets the
    highest bid back to 0.
    */
    void reset_auctioneer();

    /*
    Notifies every registered bidder, except the one who just placed the
    current highest bid, by calling their update() function.
    */
    void notify_bidders();

    /*
    Accepts a new bid. If it's higher than the current highest bid, records
    it as the new highest bid/bidder and notifies the other bidders.
    :param bid: the bid amount.
    :param bidder: the Bidder placing the bid (nullptr for the opening bid).
    */
    void accept_bid(double bid, Bidder *bidder = nullptr);

    // TODO: add any getters you need (e.g. getHighestBid(), getHighestBidder())
    // so Auction can print the auction result and bidder summary.
};
