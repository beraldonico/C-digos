import uuid
from pydantic import BaseModel, Field

class GreenhouseRead(BaseModel):
    id : str = Field(default_factory=uuid.uuid4, alias="_id")
    timestamp: int = Field(...)
    Temp: float = Field(...)
    RH: float = Field(...)
    Water_Level_Irrigation: int = Field(...)
    Water_Level_Umidity: int = Field(...)
    Soil_Moisture: int = Field(...)
    LUX_Index: int = Field(...)

    class Config:
        allow_population_by_field_name = True
        schema_extra = {
            "example": {
                "timestamp": 1643540977, 
                "Temp": 25.80, 
                "RH": 77.77, 
                "Water_Level_Irrigation": 0, 
                "Water_Level_Umidity": 0, 
                "Soil_Moisture": 8, 
                "LUX_Index": 64.17
            }
        }