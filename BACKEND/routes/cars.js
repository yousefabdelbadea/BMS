const {Car} = require('../models/car');
const express = require('express');
const { Cell } = require('../models/cell');
const { CellDetail } = require('../models/cellDetail');
const router = express.Router();

router.get(`/`, async (req, res) =>{
    const carList = await Car.find().populate('user', 'name').populate( {
        path: 'cells', populate: {path : 'cellDetails'}}).sort({'dateOfRecord': -1});

    if(!carList) {
        res.status(500).json({success: false})
    }
    res.send(carList);
})

router.get(`/:id`, async (req, res) =>{
    const car = await Car.findById(req.params.id).populate('user', 'name')
        .populate({
            path: 'cells', populate: {
                path : 'cellDetails'}
        }).sort({'cellDetails': -1})

    if(!car) {
        res.status(500).json({success: false})
    }
    res.send(car);
})


router.post('/', async (req,res)=>{
    const cells = Promise.all(req.body.cells.map(async (cell) =>{
        const newCellDetails = Promise.all(cell.cellDetails.map(async (cellDetails) =>{
            let newCellDetail = new CellDetail({
                temperature: cellDetails.temperature,
                current: cellDetails.current,
                voltage:cellDetails.voltage,
                percentage:cellDetails.percentage
            })
            newCellDetail = await newCellDetail.save();
            return newCellDetail._id
        }))

        const  newCellDetailsIds = await newCellDetails
        let newCell = new Cell({
            number: cell.number,
            model: cell.model,
            temperature: cell.temperature,
            current: cell.current,
            voltage: cell.voltage,
            status: cell.status,
            percentage: cell.percentage,
            cellDetails: newCellDetailsIds
        })
        newCell = await newCell.save();

        return newCell._id;
    }))
     const cellResolvedIds =  await cells;

    let car = new Car({
        cells: cellResolvedIds,
        number:req.body.number,
        model: req.body.model,
        isOnCharging: req.body.isOnCharging,
        percentage: req.body.percentage,
        dateOfInsertion: req.body.dateOfInsertion,
        status: req.body.status,
        user: req.body.user,
    })
    car = await car.save();

    if(!car)
        return res.status(400).send('the order cannot be created!')

    res.send(car);
})

router.patch('/:id',async (req, res)=> {
    let cell = await Cell.findById(req.params.id);

    const newCellDetails = Promise.all(req.body.cellDetails.map(async (cellDetail) =>{
        let newCellDetail = new CellDetail({
            temperature: cellDetail.temperature,
            current: cellDetail.current,
            voltage:cellDetail.voltage,
            percentage:cellDetail.percentage
        })
        newCellDetail = await newCellDetail.save();
        return newCellDetail._id
    }))
    const  newCellDetailsIds = await newCellDetails
    cell.cellDetails = cell.cellDetails.concat(newCellDetailsIds);
    await cell.save();
    if(!cell)
        return res.status(400).send('the order cannot be update!')

    res.send(cell);
})

router.put('/:id',async (req, res)=> {
    const car = await Car.findByIdAndUpdate(
        req.params.id,
        {
            status: req.body.status
        },
        { new: true}
    )

    if(!car)
        return res.status(400).send('the order cannot be update!')

    res.send(car);
})


router.delete('/:id', (req, res)=>{
    Car.findByIdAndRemove(req.params.id).then(async car =>{
        if(car) {
            await car.cells.map(async cell => {
                await Cell.findByIdAndRemove(cell)
            })
            return res.status(200).json({success: true, message: 'the order is deleted!'})
        } else {
            return res.status(404).json({success: false , message: "order not found!"})
        }
    }).catch(err=>{
        return res.status(500).json({success: false, error: err})
    })
});


module.exports =router;
