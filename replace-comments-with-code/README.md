# Clean code: replace comments with code, in C++

> Let the code say what it does, so no comment can drift into a lie.

[Watch the video](https://www.youtube.com/watch?v=3S0moCAqI3w) · [Step through it interactively](https://illbebackend.dev/lessons/replace-comments-with-code/cpp/)

## The problem

Loyalty members now cancel free from 7 days. The if changed, and the comment above it didn't.

## Steps

Each folder holds the complete `cancellation_policy.cpp` after that step, and every one compiles. Diff two neighbouring folders to see a single refactoring.

| Step | What changes | Move |
|---|---|---|
| [01](step-01-a-comment-on-every-rule/) | A comment on every rule: fee works out what a guest pays to cancel. Each rule has a comment above it that says what the line does. | Before |
| [02](step-02-the-comment-still-says-14/) | The comment still says 14: Loyalty members now cancel free from 7 days. The if changed, and the comment above it didn't. | Code smell |
| [03](step-03-back-it-out-then-name-things/) | Back it out, then name things: The loyalty rule comes out. Each comment that says what becomes a name, and then the comment goes. | Plan |
| [04](step-04-name-the-day-count/) | Name the day count: d becomes daysBeforeCheckIn, and the comment that explained d is gone. | Rename Variable |
| [05](step-05-name-the-fourteen/) | Name the fourteen: 14 becomes the constexpr constant FREE_CANCELLATION_DAYS. | Replace Magic Number |
| [06](step-06-name-the-two/) | Name the two: 2 becomes LAST_MINUTE_DAYS. The condition wraps onto a second line. | Replace Magic Number |
| [07](step-07-name-the-rate-code/) | Name the rate code: 'N' becomes NON_REFUNDABLE. | Replace Magic Number |
| [08](step-08-the-free-rule-gets-a-name/) | The free rule gets a name: isFreeCancellation(days) holds the 14-day check. Its comment is gone. | Extract Method |
| [09](step-09-full-pay-gets-a-name/) | Full pay gets a name: paysInFull(b, days) holds the rate and last-minute check. Its comment is gone. | Extract Method |
| [10](step-10-name-the-half/) | Name the half: f becomes halfTotal, and the comment that said so is gone. | Rename Variable |
| [11](step-11-name-one-night-s-price/) | Name one night's price: total divided by nights moves into nightlyPrice(b). | Extract Method |
| [12](step-12-one-comment-stays/) | One comment stays: The contract comment gives a reason the code can't show, so it stays. | Keep the why |
| [13](step-13-loyalty-in-one-place/) | Loyalty, in one place: isFreeCancellation takes the booking and checks LOYALTY_FREE_DAYS for loyal guests. paysInFull and nightlyPrice didn't change. | Payoff |

## Takeaways

- **Use it when:** A comment tells you what the next line or block does.
- **Skip it when:** The comment explains why, like a contract, a bug workaround or a law, or it documents a public API.
- **Spot it by:** A comment above a short block, a one-letter variable, or a bare number in a condition.
- **Already in C++:** Chrono durations carry their unit in the type, so fourteen days needs no comment.
