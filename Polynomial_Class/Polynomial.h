#pragma once
#include <cstdio>

#define MAX_DEGREE 50

class Polynomial {
    int degree;
    float coef[MAX_DEGREE];

public:
    Polynomial() {
        degree = 0;
        for (int i = 0; i < MAX_DEGREE; i++)
            coef[i] = 0;
    }

    void read() {
        printf("최고 차수 입력: ");
        scanf_s("%d", &degree);

        printf("계수 입력 (%d개): ", degree + 1);
        for (int i = 0; i <= degree; i++)
            scanf_s("%f", &coef[i]);
    }

    void display(const char* msg = "Poly = ") {
        printf("%s ", msg);
        for (int i = 0; i < degree; i++)
            printf("%.1fx^%d + ", coef[i], degree - i);

        printf("%.1f\n", coef[degree]);
    }

    void add(Polynomial a, Polynomial b) {
        if (a.degree > b.degree) {
            *this = a;
            for (int i = 0; i <= b.degree; i++)
                coef[i + (degree - b.degree)] += b.coef[i];
        }
        else {
            *this = b;
            for (int i = 0; i <= a.degree; i++)
                coef[i + (degree - a.degree)] += a.coef[i];
        }
    }
};
