#uvicorn --host 0.0.0.0 app.main:app --reload
#docker build -t api-greenhouse .
#docker run --env-file env_file -d --restart always --name greenhouse-container -p 8000:8000 api-greenhouse
import uvicorn
from fastapi import FastAPI
from motor.motor_asyncio import AsyncIOMotorClient

from app.routers import router 
from app.config import settings

app = FastAPI()

print(f"Connection server:{settings.DB_URL}")

@app.on_event("startup")
async def startup_db_client():
    app.mongodb_client = AsyncIOMotorClient(settings.DB_URL)
    app.mongodb = app.mongodb_client[settings.DB_NAME]

@app.on_event("shutdown")
async def shutdown_db_client():
    app.mongodb_client.close()

app.include_router(router, tags=["values"], prefix="/greenhouse")

if __name__ == "__main__":
    uvicorn.run(
        "main:app",
        host = settings.HOST,
        reload = settings.DEBUG_MODE,
        port = settings.PORT
    )