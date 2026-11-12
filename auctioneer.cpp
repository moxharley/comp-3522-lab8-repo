#include "auctioneer.hpp"

void Auctioneer::register_bidder(Bidder *bidder) {
    bidders.push_back(bidder);
}

void Auctioneer::reset_auctioneer() {
    bidders.clear();
    highest_bid = 0;
    highest_bidder = NULL;
}

void Auctioneer::notify_bidders() {
    for (Bidder *bidder : bidders) {
        if (bidder != highest_bidder) {
            bidder->update(this);
        }
    }
}

void Auctioneer::accept_bid(double bid, Bidder *bidder) {
    string bidder_name = bidder->get_name();
    if (bidder == NULL) {
        bidder_name = "Starting bid";
    }
    if (bid > highest_bid) {
        cout << bidder_name << " bidded $" << 
                bid << " in response to " << 
                highest_bidder << "'s bid of $" << 
                highest_bid << endl;
        highest_bid = bid;
        highest_bidder = bidder;
        notify_bidders();
    }
}
