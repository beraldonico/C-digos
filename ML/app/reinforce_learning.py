import random
from collections import OrderedDict
from q_table import q_table_class
from enviroment import GreenHouse

def start_training(env: GreenHouse, q_table: q_table_class):
    states = env.reset()
    alpha = 0.1
    gamma = 0.6
    epsilon = 0.2
    reward = 0
    
    while True:
        print("-------------------- New episode --------------------")
        # Take learned path or explore new actions based on the epsilon
        if random.uniform(0, 1) < epsilon:
            actions = env.action_space.sample()
            actions = clean_sample_action(actions, True)
            print(f"Random actions taken: {actions}")
            
        else:
            actions = q_table.get_actions(states)
            actions = clean_sample_action(actions, False)
            print(f"q_table actions taken: {actions}")

        # Take action    
        next_state, reward, _, info = env.step(actions) 
        
        # Recalculate
        for action, q_value in actions.items():
            max_value = q_table.get_action(next_state, action)
            new_q_value = (1 - alpha) * q_value + alpha * (reward + gamma * max_value)
            q_table.update_action(states, action, new_q_value)
        # Update Q-table
        states = env.get_observation()
        q_table.print_table()
        q_table.save_df()

def clean_sample_action(actions: dict, is_array):
    return_action = {}
    for action, value in actions.items():
        if is_array:
            return_action[action] = float(value[0])
        else:
            return_action[action] = float(value)
    return OrderedDict(return_action)

if __name__ == "__main__":
    from config import settings
    env = GreenHouse(settings.TEMP_THRESHOLD, settings.RH_THRESHOLD, settings.MOOISTURE_THRESHOLD, settings.LUX_THRESHOLD)
    q_table = q_table_class()
    start_training(env, q_table)