# Clean code: rename for intent, in C++

> Make every name say what it means, so the next change lands right.

[Watch the video](https://www.youtube.com/watch?v=PywLC9iWfjI) · [Step through it interactively](https://illbebackend.dev/lessons/rename-for-intent/cpp/)

## The problem

The new check reads l.d as days late. It counts days since checkout, so the check never fires for a late book.

## Steps

Each folder holds the complete `late_fines.cpp` after that step, and every one compiles. Diff two neighbouring folders to see a single refactoring.

| Step | What changes | Move |
|---|---|---|
| [01](step-01-a-late-fine-that-works/) | A late fine that works: Fees::calc works out a library fine from a Loan, and ReturnDesk prints it. | Before |
| [02](step-02-a-grace-period-that-never-applies/) | A grace period that never applies: The new check reads l.d as days late. It counts days since checkout, so the check never fires for a late book. | Code smell |
| [03](step-03-undo-then-rename/) | Undo, then rename: Back the grace period out. Rename each field, variable and number for what it means, then add the grace period again. | Plan |
| [04](step-04-d-becomes-daysout/) | d becomes daysOut: The Loan field d is renamed to daysOut, and its one reader follows. | Rename Field |
| [05](step-05-f-becomes-student/) | f becomes student: The flag f is true for student cards, so it is renamed to student. | Rename Field |
| [06](step-06-x-becomes-dayslate/) | x becomes daysLate: x holds days out minus the loan period, so it is renamed to daysLate. | Rename Variable |
| [07](step-07-r-becomes-dailyrate/) | r becomes dailyRate: r is what each late day costs, so it is renamed to dailyRate. | Rename Variable |
| [08](step-08-l-becomes-loan/) | l becomes loan: Both parameters named l are renamed to loan. | Rename Parameter |
| [09](step-09-name-the-loan-period/) | Name the loan period: 14 becomes the constant LOAN_DAYS. | Replace Magic Number |
| [10](step-10-name-the-two-rates/) | Name the two rates: 0.10 and 0.25 become STUDENT_RATE and STANDARD_RATE. | Replace Magic Number |
| [11](step-11-name-the-cap/) | Name the cap: 10.0 becomes MAX_FINE. | Replace Magic Number |
| [12](step-12-calc-becomes-overduefine/) | calc becomes overdueFine: calc is renamed to overdueFine, and the call in ReturnDesk follows. | Rename Method |
| [13](step-13-the-grace-period-right-the-first-time/) | The grace period, right the first time: GRACE_DAYS is added, and the existing daysLate check uses it. Loan and ReturnDesk don't change. | Payoff |

## Takeaways

- **Use it when:** You have to read a method's body to learn what one of its names means.
- **Skip it when:** A short name lives in a tiny scope and is already clear, like i in a three-line loop.
- **Spot it by:** Single letters, names like data, flag or calc, bare numbers, and comments that explain what a variable holds.
