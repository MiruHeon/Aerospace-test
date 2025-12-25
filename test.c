#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
#include <windows.h>

const double EARTH_RADIUS = 6371.0;        // km
const double GM = 398600.4418;              // km^3 / s^2 (지구 중력 상수)

// 궤도 반지름
double calc_orbit_radius(double earth_r, double height) {
    return earth_r + height;
}

// 공전 속도
double calc_orbital_speed(double gm, double r) {
    return sqrt(gm / r);
}

// 공전 주기
double calc_orbital_period(double r, double v) {
    return (2.0 * M_PI * r) / v;
}

// 각속도
double calc_angular_velocity(double T) {
    return (2.0 * M_PI) / T;
}

void calc_position(double r, double theta, double inclination, FILE* fp) {
    double x = r * cos(theta);
    double y = r * sin(theta) * cos(inclination);
    double z = r * sin(theta) * sin(inclination);

    fprintf(fp, "%.6f %.6f %.6f\n", x, y, z);
}

int main(void) {
    double height = 300.0;
    double inclination_deg = 60.0;
    double inclination = inclination_deg * (M_PI / 180.0);

    double dt = 10.0;
    double time = 0.0;
    double theta = 0.0;

    double r = calc_orbit_radius(EARTH_RADIUS, height);
    double v = calc_orbital_speed(GM, r);
    double T = calc_orbital_period(r, v);
    double w = calc_angular_velocity(T);

    printf("===== Satellite Orbit Simulation =====\n");
    printf("Orbit radius     : %.2f km\n", r);
    printf("Orbital speed    : %.5f km/s\n", v);
    printf("Orbital period   : %.2f s (%.2f min)\n", T, T / 60.0);
    printf("Angular velocity : %.8f rad/s\n", w);
    printf("Inclination      : %.1f deg\n", inclination_deg);
    printf("======================================\n");

    FILE* fp = fopen("orbit.txt", "w");
    if (fp == NULL) {
        printf("파일 열기 실패\n");
        return 1;
    }

    while (time <= T) {
        calc_position(r, theta, inclination, fp);

        theta += w * dt;
        time += dt;

        Sleep(10);
    }

    fclose(fp);

    return 0;
}
