/**
 * There are n cars at given miles away from the starting mile 0, traveling to
 * reach the mile target.
 *
 * You are given two integer arrays position and speed, both of length n, where
 * position[i] is the starting mile of the ith car and speed[i] is the speed of
 * the ith car in miles per hour.
 *
 * A car cannot pass another car, but it can catch up and then travel next to it
 * at the speed of the slower car.
 *
 * A car fleet is a single car or a group of cars driving next to each other.
 * The speed of the car fleet is the minimum speed of any car in the fleet.
 *
 * If a car catches up to a car fleet at the mile target, it will still be
 * considered as part of the car fleet.
 *
 * Return the number of car fleets that will arrive at the destination.
 *
 * Solution:
 * We pair each car’s position with the time it takes to reach the target:
 *     time = (target - position) / speed
 *
 * Then we sort cars by position in ascending order. We iterate from the car
 * closest to the target (rightmost) to the farthest (leftmost).
 *
 * We use a monotonic decreasing stack (array-based) storing times:
 * - If the current car’s time is greater than the top of the stack,
 *   it cannot catch up -> forms a new fleet -> push time
 * - Otherwise, it joins the fleet ahead (do nothing)
 *
 * Why this works:
 *
 * Key idea: A car can never pass another car in front of it.
 * So if a faster car starts behind a slower one, it will eventually
 * catch up and they will move together as a single "fleet".
 *
 * Instead of simulating movement, we compute each car’s "arrival time"
 * to the target. This lets us reason about fleets mathematically.
 *
 * After sorting by position, we process cars from right to left
 * (from closest to the target to farthest).
 *
 * - The first car (closest to target) always forms a fleet.
 * - For each next car behind:
 *     -> If its time <= time of the fleet ahead:
 *        it catches up before the target -> merges into that fleet
 *     -> If its time > time of the fleet ahead:
 *        it cannot catch up -> forms a new fleet
 *
 * Why comparing times works:
 * - Smaller time = faster arrival
 * - If a car arrives earlier (smaller time), it must slow down
 *   when it reaches the slower car ahead -> they merge
 * - If it arrives later (larger time), it never reaches the car ahead
 *
 * Why a monotonic stack:
 * - The stack stores fleet arrival times
 * - Times are in decreasing order (top is the slowest fleet so far)
 * - Each new car either:
 *     -> merges (ignored)
 *     -> or creates a new fleet (pushed)
 *
 * So each stack element = one fleet
 *
 * Time Complexity: O(n log n) (sorting)
 * Space Complexity: O(n)
 */
#include <stdlib.h>

struct car {
    int pos;
    float time;
};

int compare(const void *a, const void *b)
{
    struct car x = *(struct car *)a;
    struct car y = *(struct car *)b;

    return x.pos - y.pos;
}

struct stack_s {
    float *arr;
    int size;
    int capacity;
    int top;
};
typedef struct stack_s *stack;

stack init(int capacity)
{
    stack x = calloc(1, sizeof(struct stack_s));
    x->capacity = capacity;
    x->top = -1;
    x->size = 0;
    x->arr = calloc(capacity, sizeof(float));

    return x;
}

int is_full(stack st)
{
    return st->top >= st->capacity - 1;
}

int is_empty(stack st)
{
    return st->top == -1;
}

void push(stack st, float val)
{
    if (st == NULL) {
        return;
    }

    if (is_full(st)) {
        st->capacity *= 2;
        st->arr = realloc(st->arr, st->capacity * sizeof(float));
    }

    st->arr[++st->top] = val;
    st->size++;
}

float peek(stack st)
{
    if (is_empty(st)) {
        return -1;
    }

    return st->arr[st->top];
}

int carFleet(int target,
             int *position,
             int positionSize,
             int *speed,
             int speedSize)
{
    struct car *cars = calloc(positionSize, sizeof(struct car));
    int i;
    stack st = init(positionSize);

    for (i = 0; i < positionSize; i++) {
        cars[i].pos = position[i];
        cars[i].time = (float)(target - position[i]) / speed[i];
    }

    qsort(cars, positionSize, sizeof(struct car), compare);

    for (i = positionSize - 1; i >= 0; i--) {
        if (is_empty(st) || peek(st) < cars[i].time) {
            push(st, cars[i].time);
        }
    }

    free(cars);
    int res = st->size;
    free(st->arr);
    free(st);
    return res;
}

int main(void)
{
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};
    int res = carFleet(12, position, 5, speed, 5);
    return EXIT_SUCCESS;
}
