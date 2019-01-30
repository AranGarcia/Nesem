#ifndef NESEM_APU_H
#define NESEM_APU_H


#include <array>
#include <cstdint>

class APU {
public:
    uint8_t access_registers(uint16_t addr, uint8_t data = 0);

    // The vertical clock signal is the only register which is read from
    uint8_t read_mstrctrl() const;

private:

    /*
     * APU Registers:
     * --------------
     * Pulse 1: $4000-$4003
     * Pulse 2: $4004-$4007
     * Triangle: $4008-$400B
     * Noise: $400C-$400F
     * Delta Modulation: $4010-$4013
     *
     */
    // Pulse 1
    uint8_t pulse1_ctrl;
    uint8_t pulse1_ramp_ctrl;
    uint8_t pulse1_fine_tune; //Fine tune
    uint8_t pulse1_coarse_tune; //Coarse tune

    // Pulse 2:
    uint8_t pulse2_ctrl;
    uint8_t pulse2_ramp_ctrl;
    uint8_t pulse2_fine_tune; //Fine tune
    uint8_t pulse2_coarse_tune; //Coarse tune

    // Triangle: $4008-$400B
    uint8_t tri_ctrl1;
    uint8_t tri_ctrl2;
    uint8_t tri_freq1;
    uint8_t tri_freq2;

    // Noise
    uint8_t noise_ctrl;
    // No register in address $400D
    uint8_t noise_freq1;
    uint8_t noise_freq2;

    // Delta Modulation:
    uint8_t delta_ctrl;
    uint8_t delta_da;
    uint8_t delta_addr;
    uint8_t delta_data_len;

    uint8_t mstrctrl;

private:
    // $4015
    uint8_t delta_frame_ctr;   // $4017    Yes, this is also the same address for the joystick
};


#endif //NESEM_APU_H
