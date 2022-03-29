from gym import Env, spaces
from db_module import get_avg, get_hist, save_hist, generate_document
from client import send_action
import time

class GreenHouse(Env):
    def __init__(self, temp_threshold, rh_threshold, moister_threshold, lux_threshold):
        super().__init__()

        # Define of observation space
        self.observation_space = spaces.Dict({ 
                                    'Temp': spaces.Discrete(3, start=-1),
                                    'RH': spaces.Discrete(3, start=-1),
                                    'Soil_Moisture': spaces.Discrete(2, start=-1),
                                    'LUX_Index': spaces.Discrete(2, start=-1)
                                })
        self.observation_space.n = (3, 3, 2, 2)

        # Define an action space ranging from 0 to 6
        self.action_space = spaces.Dict({ 
                                    'heater': spaces.Box(low=0, high=1, shape=(1,)),
                                    'AC': spaces.Box(low=0, high=1, shape=(1,)),
                                    'ventilation': spaces.Box(low=0, high=1, shape=(1,)),
                                    'irrigation': spaces.Box(low=0, high=1, shape=(1,)),
                                    'light': spaces.Box(low=0, high=1, shape=(1,)),
                                    'humidifier': spaces.Box(low=0, high=1, shape=(1,)),
                                })
        self.action_space.n = (2, 2, 2, 2, 2, 2)

        # Greenhouse variables objective
        self.temp_threshold = temp_threshold
        self.rh_threshold = rh_threshold
        self.moister_threshold = moister_threshold
        self.lux_threshold = lux_threshold

    def step(self, actions):
        state = {}
        reward = 0
        done = False
        info = {}

        # apply the action to the greenhouse
        send_action(actions)

        # save action and varible on greenhouse_history
        document = generate_document(self.values, actions, self.reward, reward)
        save_hist(document)

        time.sleep(60) #1 minute sleep to wait greehouse varibles variation
        
        # check variaves and reward if state is better than before
        state = self.get_observation()
        reward = self.give_reward(self.values, actions)
        self.reward += reward

        # save state, action and reward after action
        document = generate_document(self.values, actions, self.reward, reward)
        save_hist(document)

        return state, reward, done, info
    
    def reset(self):
        try:
            self.values = get_hist()
            self.state, self.reward = self.convert_read_to_states(self.values), self.values["reward"]
        except Exception:
            self.values = get_avg()
            self.state, self.reward = self.convert_read_to_states(self.values), 0
        return self.state

    def render(self):#*not used in our case
        pass

    def close(self):#*not used in our case
        pass

    def give_reward(self, values, action):
        reward = 0
        if 1 in action.values():
            if self.state["Temp"] == -1 and values["Temp"] > self.values["Temp"] or \
            self.state["Temp"] == 1 and values["Temp"] < self.values["Temp"]:
                reward += 1

            if self.state["RH"] == -1 and values["RH"] > self.values["RH"] or \
            self.state["RH"] == 1 and values["RH"] < self.values["RH"]:
                reward += 1
            
        if action["irrigation"] == 1 and self.state["Soil_Moisture"] == -1 and values["Soil_Moisture"] > self.values["Soil_Moisture"]:
            reward += 1
        
        if action["light"] == 1 and self.state["LUX_Index"] == -1 and values["LUX_Index"] > self.values["LUX_Index"]:
            reward += 1

        return reward

    def get_observation(self):
        self.values = get_avg()
        return self.convert_read_to_states(self.values)
    
    def convert_read_to_states(self, space_observation):
        state = {}
        if space_observation["Temp"] < self.temp_threshold - 1:
            state["Temp"] = -1
        elif space_observation["Temp"] > self.temp_threshold + 1:
            state["Temp"] = 1
        else:
            state["Temp"] = 0

        if space_observation["RH"] < self.rh_threshold - 5:
            state["RH"] = -1
        elif space_observation["RH"] > self.rh_threshold + 5:
            state["RH"] = 1
        else:
            state["RH"] = 0

        if space_observation["Soil_Moisture"] < self.moister_threshold:
            state["Soil_Moisture"] = -1
        else:
            state["Soil_Moisture"] = 0

        if space_observation["LUX_Index"] < self.lux_threshold:
            state["LUX_Index"] = -1
        else:
            state["LUX_Index"] = 0

        return state

if __name__ == "__main__":
    from config import settings
    env = GreenHouse(settings.TEMP_THRESHOLD, settings.RH_THRESHOLD, settings.MOOISTURE_THRESHOLD, settings.LUX_THRESHOLD)
    test = env.action_space.sample()
    print(test)