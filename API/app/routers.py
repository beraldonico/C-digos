from fastapi import APIRouter, Body, HTTPException, Request, status
from fastapi.encoders import jsonable_encoder
from fastapi.responses import JSONResponse

from app.Model import GreenhouseRead

router = APIRouter()
    
@router.post("/new_read")
async def insert_read(request: Request, read: GreenhouseRead = Body(...)):
    read = jsonable_encoder(read)
    response = await request.app.mongodb["GreenHouse_Values"].insert_one(read)
    if response:
        return JSONResponse(status_code=status.HTTP_201_CREATED)
    raise HTTPException(status_code=status.HTTP_400_BAD_REQUEST)