import math


class sim_config:
    def __init__(self):
        self.battery_type_to_volume_L = {
            #https://en.wikipedia.org/wiki/List_of_battery_sizes
            'AA':   ((14.5 * 1/2)**2 * math.pi * 50.5) * 1E-6,
            'AAA':  ((10.5 * 1/2)**2 * math.pi * 44.5) * 1E-6,
            'CR123A': ((17 * 1/2)**2 * math.pi * 34.5) * 1E-6,
            'CR2032':  ((20 * 1/2)**2 * math.pi * 3.2) * 1E-6,
            'HTC-titanate': ((10 * 1/2)**2 * math.pi * 20) * 1E-6,
        }
        self.chemistry_energy_density_WhpL = {
            # https://en.wikipedia.org/wiki/Comparison_of_commercial_battery_types
            'Alkaline': 320,
            'LiMnO2':   510,
            # https://en.wikipedia.org/wiki/Lithium%E2%80%93titanate_battery
            'titanate': 177,
            'LiPo':     500,
            'LiIon':    475,
        }
        self.design_config = {
            'name' : 'design',
            'intermittent' : True,
            'intermittent_mode' : 'periodic', # periodic or opportunistic
            'operating_voltage_V' : 3.3,
            'boost_efficiency' : 0.8,
            'frontend_efficiency' : 0.8,
            'secondary' : 'cap',
            'secondary_max_percent': 80.1,
            'secondary_min_percent': 80,
        }
        self.dataset = {
            'name': 'dataset',
            'filename': '../enhants/numpy_arrays/SetupA.npy',
            'resolution_s': 30,
        }
        self.workload_config = {
            'name' : 'sense_and_send',
            'sleep_current_A' : 1.5E-6,
            'startup_energy_J' : 6E-6,
            'sensor_energy_J': 6.11E-6, # i2c communication + sensor energy
            'radio_energy_J': 1.15E-4, # one BLE advertisement
            'period_s': 10,
        }
        self.secondary_cap = {
            'name' : 'secondary',
            'type' : 'capacitor',
            'charge_discharge_eff' : 0.80,
            'capacity_J': (1000E-6) * (3.3**2),
            'min_capacity_J': (1000E-6) * (0.4**2),
        }
        self.secondary_super_cap = {
            'name' : 'secondary',
            'type' : 'capacitor',
            'charge_discharge_eff' : 0.75,
            'capacity_J': (1000E-6 + 7.5E-3) * (3.3**2),
            'min_capacity_J': (1000E-6 + 7.5E-3) * (0.4**2),
        }
        self.secondary_configs = {
            'cap' : self.secondary_cap,
            'super_cap' : self.secondary_super_cap,
        }
        self.solar_config = {
            'name' : 'solar',
            'nominal_voltage_V' : 2.5,
            'area_cm2' : 10,
            'efficiency' : 0.19,
        }
        self.config_list = [self.design_config, self.secondary_configs[self.design_config['secondary']], self.solar_config]

sweep_vars = [
                [('solar', 'area_cm2'), [i*10**exp for exp in range(0, 2) for i in range(1,10)], 'both']
                #[('secondary', 'capacity_mAh'), [i*10**exp for exp in range(-5, 2) for i in range(1, 10, 2)], 'both'],
             ]
