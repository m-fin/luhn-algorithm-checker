#!/bin/sh
# Checks ./luhn against widely published test numbers and malformed input.
# Valid PANs are public test numbers (Stripe and the usual textbook samples),
# not real accounts. Check digits on a few of those are altered for failures.

set -eu

cd "$(dirname "$0")"

bin=./luhn
failures=0

if [ ! -x "$bin" ]; then
    echo "missing $bin (run make first)" >&2
    exit 1
fi

expect() {
    input=$1
    want=$2
    got=$(printf '%s\n' "$input" | "$bin")
    if [ "$got" != "Number: $want" ]; then
        printf 'FAIL: [%s]\n  expected: Number: %s\n  got:      %s\n' "$input" "$want" "$got" >&2
        failures=$((failures + 1))
    else
        printf 'ok  %-12s %s\n' "$want" "$input"
    fi
}

# American Express, 15 digits, 34/37
expect 378282246310005 AMEX
expect 371449635398431 AMEX

# Mastercard, 16 digits, 51-55
expect 5555555555554444 MASTERCARD
expect 5105105105105100 MASTERCARD
expect 5200828282828210 MASTERCARD

# Visa, 13 or 16 digits, leading 4
expect 4111111111111111 VISA
expect 4012888888881881 VISA
expect 4222222222222 VISA
expect 4242424242424242 VISA
expect 4000000000000002 VISA

# Same Visa test number with surrounding whitespace, and a leading plus,
# which the previous scanf parser accepted.
expect '  4111111111111111' VISA
expect '4111111111111111   ' VISA
expect '+4111111111111111' VISA

# Bad checksum: public test numbers with the check digit changed.
expect 4111111111111112 INVALID
expect 4012888888881882 INVALID
expect 4222222222223 INVALID
expect 378282246310006 INVALID
expect 5555555555554443 INVALID

# Wrong length, including a 15-digit truncation of the Visa test number.
expect 1234567890 INVALID
expect 411111111111111 INVALID

# Luhn-valid published test numbers this program does not classify:
# Discover, 14-digit Diners Club, and Mastercard's 2-series (2221-2720).
expect 6011111111111117 INVALID
expect 30569309025904 INVALID
expect 2223003122003222 INVALID

# A leading zero does not change the numeric value (same as the old %ld parse).
expect '04111111111111111' VISA

# Not an integer.
expect abc INVALID
expect '' INVALID
expect '   ' INVALID
expect 4111111111111111abc INVALID
expect '4111 1111 1111 1111' INVALID
expect '-4111111111111111' INVALID
expect 9999999999999999999 INVALID

# A value with no trailing newline is still a complete entry at EOF.
got=$(printf '%s' '4111111111111111' | "$bin")
if [ "$got" != "Number: VISA" ]; then
    printf 'FAIL: EOF without newline got [%s]\n' "$got" >&2
    failures=$((failures + 1))
else
    printf 'ok  %-12s %s\n' VISA '(no trailing newline)'
fi

if [ "$failures" -ne 0 ]; then
    printf '%s test(s) failed\n' "$failures" >&2
    exit 1
fi

echo "all tests passed"
