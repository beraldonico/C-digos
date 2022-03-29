from tabulate import tabulate
from collections import OrderedDict
import platform
import numpy as np
import pandas as pd

class q_table_class:
    def __init__(self):
        try:
            if platform.system() == "Windows":
                self.df_q_table = pd.read_csv("q_table.csv", index_col=[0,1,2,3])
            else:
                self.df_q_table = pd.read_csv("/q_table/q_table.csv", index_col=[0,1,2,3])
            print("Using existing csv q_table")
        except FileNotFoundError:
            print("Creating new q_table")
            index_names = ["Temp", "RH", "Soil_Moisture", "LUX_Index"]
            column_names = ['AC', 'heater', 'humidifier', 'irrigation', 'light', 'ventilation']
            states = [[-1, 0, 1], [-1, 0, 1], [-1,0], [-1,0]]

            states_index = pd.MultiIndex.from_product(states, names=index_names)
            self.df_q_table = pd.DataFrame(np.zeros([36,6], dtype=int), index=states_index, columns=column_names)

    def get_actions(self, states):
        return OrderedDict(self.df_q_table.loc[states["Temp"], states["RH"], states["Soil_Moisture"], states["LUX_Index"]])

    def get_action(self, states, action):
        return self.df_q_table.loc[states["Temp"], states["RH"], states["Soil_Moisture"], states["LUX_Index"]][action]

    def update_action(self, states, action, new_value):
        self.df_q_table.loc[(states["Temp"], states["RH"], states["Soil_Moisture"], states["LUX_Index"]),[action]] = new_value
    
    def print_table(self):
        print(tabulate(self.df_q_table, headers='keys', tablefmt='psql'))

    def save_df(self):
        if platform.system() == "Windows":
            self.df_q_table.to_csv("q_table.csv")
        else:
            self.df_q_table.to_csv("/q_table/q_table.csv")

if __name__ == "__main__":
    from config import settings
    from enviroment import GreenHouse
    env = GreenHouse(settings.TEMP_THRESHOLD, settings.RH_THRESHOLD, settings.MOOISTURE_THRESHOLD, settings.LUX_THRESHOLD)
    q_table = q_table_class()
    q_table.save_df()