#docker build -t greenhouse-ml .
#docker volume create q_table
#docker run --env-file env_file -d --restart always -v q_table:/q_table --name greenhouse-ml-container greenhouse-ml
from enviroment import GreenHouse
from reinforce_learning import start_training
from config import settings
from q_table import q_table_class

if __name__ == "__main__":
    env = GreenHouse(settings.TEMP_THRESHOLD, settings.RH_THRESHOLD, settings.MOOISTURE_THRESHOLD, settings.LUX_THRESHOLD)
    q_table = q_table_class()
    start_training(env, q_table)