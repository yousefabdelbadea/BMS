const {Car} = require('../models/car');
const express = require('express');
const { Cell } = require('../models/cell');
const {User} = require('../models/user');
const { CellDetail } = require('../models/cellDetail');
const router = express.Router();
const mongoose = require('mongoose');


router.get(`/`, async (req, res) =>{
    const carList = await Car.find( function (err, car) {
        if (err){
            res.status(400).json({success: false, message: 'cars not found', error: err})
        }
    }).populate('user', 'name').populate( {
        path: 'cells', populate: {path : 'cellDetails'}}).sort({'dateOfRecord': -1});

    if(!carList) {
        res.status(500).json({success: false})
    }
    res.send(carList);
})

router.get(`/:id`, async (req, res) =>{
    const car = await Car.findById(req.params.id , function (err, car) {
        if (err){
            res.status(400).json({success: false, message: ' no car with the given id', error: err})
        }
    }).populate('user', 'name')
        .populate({
            path: 'cells', populate: {
                path : 'cellDetails'}
        }).sort({'cellDetails': -1})

    if(!car) {
        res.status(500).json({success: false})
    }
    res.send(car);
})

//get cell by number
router.get(`/:carId/:cellNumber`, async (req, res) =>{
    const car = await Car.findById(req.params.carId , function (err, car) {
        if (err){
            res.status(400).json({success: false, message: ' no car with the given id', error: err})
        }
    }).populate('user', 'name')
        .populate({
            path: 'cells', populate: {
                path : 'cellDetails'}
        }).sort({'cellDetails': -1})

    if(!car) {
        res.status(400).json({success: false, message:"no car with the given id"})
    }
    if (car.cells.length-1 < req.params.cellNumber){
        res.status(400).json({success: false, message: ' no cell with the given number'})
    }
    const cell = car.cells[+req.params.cellNumber]
    if (!cell){
        res.send('No cell was found for this number ' + req.params.cellNumber)
    }
    res.send(cell);
})

router.post('/', async (req,res)=>{
    // const user = await User.findById(req.body.user, (err)=> {
    //     if (err) {
    //         res.status(400).send('No user was found, ' + err)
    //     }
    // })

        Car.findOne({'number':req.body.number}, function (err, car) {
            if (car) {
            res.status(400).json({
                carId:car._id,
                message:'There is a car with the same number',
                success : false
            })
        }
    })

    if (!req.body.cells) {
        let cellsArray = [];
        if (req.body.numberOfCells > 20) {
            return res.status(404).send('only a maximum of 20 cell for each car is allowed')
        }
        for (let i = 0; i < req.body.numberOfCells; i++) {
            let cell = new Cell({})
            await cell.save().catch(err => {
                if (err)
                    res.status(500).json({
                        success:false, message:err.message
                    })
            });
            cellsArray.push(cell._id);
        }
        let car = new Car({
            number: req.body.number,
            model: req.body.model,
            isOnCharging: req.body.isOnCharging,
            percentage: req.body.percentage,
            dateOfInsertion: req.body.dateOfInsertion,
            status: req.body.status,
            user: req.body.user,
            cells : cellsArray
        })
        car = await car.save().catch(err => {
            if (err)
                res.status(500).json({
                    success:false, message:err.message
                })
        });

        if (!car)
            return res.status(404).send('the car cannot be created!')

        res.send(car);
    }
    const cells = Promise.all(req.body.cells.map(async (cell) =>{
        const newCellDetails = Promise.all(cell.cellDetails.map(async (cellDetails) =>{
            let newCellDetail = new CellDetail({
                temperature: cellDetails.temperature,
                current: cellDetails.current,
                voltage:cellDetails.voltage,
                percentage:cellDetails.percentage,
                dateOfRecord:cellDetails.dateOfRecord
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
        return res.status(400).send('the car cannot be created!')

    res.send(car);
})

router.post('/:carId/cells', async (req,res)=>{
    const car = await Car.findById(req.params.carId, (err,)=>{
        if (err) {
            res.send('No car was found, '+err).status(404)
        }
    });

    const cells = Promise.all(req.body.cells.map(async (cell) =>{
        if (cell.cellDetails) {
            const newCellDetails = Promise.all(cell.cellDetails.map(async (cellDetails) => {
                let newCellDetail = new CellDetail({
                    temperature: cellDetails.temperature,
                    current: cellDetails.current,
                    voltage: cellDetails.voltage,
                    percentage: cellDetails.percentage,
                    dateOfRecord: cellDetails.dateOfRecord
                })
                newCellDetail = await newCellDetail.save();
                return newCellDetail._id
            }))

            const newCellDetailsIds = await newCellDetails
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
        }
        else {
            let newCell = new Cell({
                number: cell.number,
                model: cell.model,
                temperature: cell.temperature,
                current: cell.current,
                voltage: cell.voltage,
                status: cell.status,
                percentage: cell.percentage,
            })
            newCell = await newCell.save();

            return newCell._id;
        }
    }))
    const cellResolvedIds =  await cells;
    for (let i=0; i<cellResolvedIds.length; i++) {
        let newCellIds = mongoose.Types.ObjectId(cellResolvedIds[i]);
        car.cells.unshift(newCellIds);
    }
    car.markModified('cells')
    await car.save();
    if(!car)
        return res.status(400).send('the cell cannot be updated!')

        res.send(car);


});


// post cell
router.post('/:carId/:cellNumber', async (req,res)=>{
    console.log('done at /:carId/:cellNumber ')
    const car = await Car.findById(req.params.carId, (err,)=>{
        if (err) {
            res.status(400).json({
                message: 'The car cannot be found',
                success: false,
                error: err.message
            })
        }
    });

    if (!req.body.cellDetails) {
        let newCell = new Cell({
            number: req.body.number,
            model: req.body.model,
            temperature: req.body.temperature,
            current: req.body.current,
            voltage: req.body.voltage,
            status: req.body.status,
            percentage: req.body.percentage,
        })
        newCell = await newCell.save();
        const cellResolvedId =  await newCell._id;
        car.cells[+req.params.cellNumber] = cellResolvedId
        car.markModified('cells')
        // await Car.updateOne({'_id':req.params.carId}), {cells:car.cells};
        await car.save();
        if(!car)
            return res.status(400).send('the cell cannot be updated!')
        res.send(car);
    }
    const newCellDetails = Promise.all(req.body.cellDetails.map(async (cellDetails) =>{
        let newCellDetail = new CellDetail({
            temperature: cellDetails.temperature,
            current: cellDetails.current,
            voltage:cellDetails.voltage,
            percentage:cellDetails.percentage,
            dateOfRecord:cellDetails.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        return newCellDetail._id
    }))

        const  newCellDetailsIds = await newCellDetails

        let newCell = new Cell({
            number: req.body.number,
            model: req.body.model,
            temperature: req.body.temperature,
            current: req.body.current,
            voltage: req.body.voltage,
            status: req.body.status,
            percentage: req.body.percentage,
            cellDetails: newCellDetailsIds
        })
        newCell = await newCell.save();

       const cellResolvedId =  await newCell._id;
       car.cells[+req.params.cellNumber] = cellResolvedId
       car.markModified('cells')
    // await Car.updateOne({'_id':req.params.carId}), {cells:car.cells};
   await car.save();
    if(!car)
        return res.status(400).send('the cell cannot be updated!')
    res.send(car.cells);
});

//post cellDetails given cell id with body

router.post('/cell/cellDetails/:carId', async (req,res)=>{
    let car = await Car.findById(req.params.carId,function (err,car) {
        if (!car) {
            res.status(404).json({
                success: false,
                message: 'Cannot find a car with the given id',
                error: err.message
            })
        }
    });


    if (!Array.isArray(req.body.cellDetails) && !req.body.hasOwnProperty('cellDetails')){
        if (car.cells.length-1 < +req.body.cellId) {
            res.status(400).json({
                message: 'no car with given carId',
                success:false,
                noOfCells: car.cells.length,
                maxId: car.cells.length - 1
            })
        }
        let newCellDetail = new CellDetail({
            temperature: req.body.temperature,
            current: req.body.current,
            voltage:req.body.voltage,
            percentage:req.body.percentage,
            dateOfRecord:req.body.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        let cell = await Cell.findById(car.cells[+req.body.cellId]._id).catch(err => {
            res.status(400).json({
                message: 'no cell with given cellId',
                error: err.message,
                success:false,
                noOfCells: car.cells.length
            })
        });
        let newCellDetailsId = mongoose.Types.ObjectId(newCellDetail._id);
        cell.cellDetails.unshift(newCellDetailsId)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
        cell.markModified('cellDetails');
        await cell.save();
        if(!cell)
            return res.status(400).send('the cell cannot be updated!')
        res.send(cell);
    }
    if (!Array.isArray(req.body.cellDetails) && req.body.hasOwnProperty('cellDetails')){
        if (car.cells.length-1 < +req.body.cellDetails.cellId) {
            res.status(400).json({
                message: 'no cell with the given cellId',
                success:false,
                noOfCells: car.cells.length,
                maxId: car.cells.length - 1
            })
        }
        let newCellDetail = new CellDetail({
            temperature: req.body.cellDetails.temperature,
            current: req.body.cellDetails.current,
            voltage:req.body.cellDetails.voltage,
            percentage:req.body.cellDetails.percentage,
            dateOfRecord:req.body.cellDetails.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        let cell = await Cell.findById(car.cells[+req.body.cellDetails.cellId]._id);
        let newCellDetailsId = mongoose.Types.ObjectId(newCellDetail._id);
        cell.cellDetails.unshift(newCellDetailsId)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
        cell.markModified('cellDetails');
        await cell.save();
        if(!cell)
            return res.status(400).send('the cell cannot be updated!')
        res.send(cell);
    }
    if (Array.isArray(req.body.cellDetails)) {
        const newCellDetails = Promise.all(req.body.cellDetails.map(async (cellDetail) => {
            if (car.cells.length-1 < +cellDetail.cellId) {
                res.status(400).json({
                    message: 'no cell with given id',
                    success:false,
                    noOfCells: car.cells.length,
                    maxId: car.cells.length - 1
                })
            }
            let newCellDetail = new CellDetail({
                temperature: cellDetail.temperature,
                current: cellDetail.current,
                voltage: cellDetail.voltage,
                percentage: cellDetail.percentage,
                dateOfRecord: cellDetail.dateOfRecord
            })
            newCellDetail = await newCellDetail.save();
            const newCellDetailsId = newCellDetail._id
            let cell = await Cell.findById(car.cells[+cellDetail.cellId]._id);
            if(!cell){
                res.send('no cell with the given id')
            }
            cell.cellDetails.unshift(newCellDetailsId)
            cell.markModified('cellDetails');
            cell.save();
        }))
        // let cell = await Cell.findById(car.cells[+req.params.cellNumber]._id);
        // cell.cellDetails = newCellDetailsIds.reverse().concat(cell.cellDetails);
        car.markModified('cells')
        await car.save();
        if (!car)
            return res.status(400).send('the cell cannot be update!')
        res.send(await Car.findById(car._id).populate('user', 'name')
            .populate({
                path: 'cells', populate: {
                    path : 'cellDetails'}
            }).sort({'cellDetails': -1}));
    }
});


//post cellDetails

router.post('/:carId/:cellNumber/cellDetails', async (req,res)=>{
    let car = await Car.findById(req.params.carId);
    if (!car){
        res.send('No car was found').status(400)
    }
    console.log(car.cells.length)
    if (car.cells.length-1 < +req.params.cellNumber){
        res.status(400).send('no cell with the given number')
    }
    if (!Array.isArray(req.body.cellDetails) && !req.body.hasOwnProperty('cellDetails')){
        console.log('done here')
        let newCellDetail = new CellDetail({
            temperature: req.body.temperature,
            current: req.body.current,
            voltage:req.body.voltage,
            percentage:req.body.percentage,
            dateOfRecord:req.body.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        let cell = await Cell.findById(car.cells[+req.params.cellNumber]._id);
        if(!cell){
            res.send('No cell found').status(404)
        }
        let newCellDetailsId = mongoose.Types.ObjectId(newCellDetail._id);
        cell.cellDetails.unshift(newCellDetailsId)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
        cell.markModified('cellDetails');
        await cell.save();
        if(!cell)
            return res.status(400).send('the cell cannot be updated!')
        res.send(cell);
    }
    if (!Array.isArray(req.body.cellDetails) && req.body.hasOwnProperty('cellDetails')){
        console.log('done here')
        let newCellDetail = new CellDetail({
            temperature: req.body.cellDetails.temperature,
            current: req.body.cellDetails.current,
            voltage:req.body.cellDetails.voltage,
            percentage:req.body.cellDetails.percentage,
            dateOfRecord:req.body.cellDetails.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        let cell = await Cell.findById(car.cells[+req.params.cellNumber]._id);
        if(!cell){
            res.send('No cell found').status(404)
        }
        let newCellDetailsId = mongoose.Types.ObjectId(newCellDetail._id);
        cell.cellDetails.unshift(newCellDetailsId)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
        cell.markModified('cellDetails');
        await cell.save();
        if(!cell)
            return res.status(400).send('the cell cannot be updated!')
        res.send(cell);
    }
    if (Array.isArray(req.body.cellDetails)) {
        const newCellDetails = Promise.all(req.body.cellDetails.map(async (cellDetails) => {
            let newCellDetail = new CellDetail({
                temperature: cellDetails.temperature,
                current: cellDetails.current,
                voltage: cellDetails.voltage,
                percentage: cellDetails.percentage,
                dateOfRecord: cellDetails.dateOfRecord
            })
            newCellDetail = await newCellDetail.save();
            return newCellDetail._id
        }))
        const newCellDetailsIds = await newCellDetails
        let cell = await Cell.findById(car.cells[+req.params.cellNumber]._id);
        if(!cell){
            res.send('No cell found').status(404)
        }
        cell.cellDetails = newCellDetailsIds.reverse().concat(cell.cellDetails);
        cell.markModified('cellDetails')
        await cell.save();
        if (!cell)
            return res.status(400).send('the cell cannot be update!')
        res.send(cell);
    }
});

router.patch('/:carId/:cellNumber', async (req,res)=>{
    let car = await Car.findById(req.params.carId);
    if (!car){
        res.send('No car found').status(404)
    }
    if (!Array.isArray(req.body.cellDetails) && !req.body.hasOwnProperty('cellDetails')){
        console.log('done here')
        let newCellDetail = new CellDetail({
            temperature: req.body.temperature,
            current: req.body.current,
            voltage:req.body.voltage,
            percentage:req.body.percentage,
            dateOfRecord:req.body.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        let cell = await Cell.findById(car.cells[+req.params.cellNumber]);
        let newCellDetailsId = mongoose.Types.ObjectId(newCellDetail._id);
        cell.cellDetails.unshift(newCellDetailsId)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
        cell.markModified('cellDetails');
        await cell.save();
        if(!cell)
            return res.status(400).send('the cell cannot be updated!')
        res.send(cell);
    }
    if (!Array.isArray(req.body.cellDetails) && req.body.hasOwnProperty('cellDetails')){
        console.log('done here')
        let newCellDetail = new CellDetail({
            temperature: req.body.cellDetails.temperature,
            current: req.body.cellDetails.current,
            voltage:req.body.cellDetails.voltage,
            percentage:req.body.cellDetails.percentage,
            dateOfRecord:req.body.cellDetails.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        let cell = await Cell.findById(car.cells[+req.params.cellNumber]);
        let newCellDetailsId = mongoose.Types.ObjectId(newCellDetail._id);
        cell.cellDetails.unshift(newCellDetailsId)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
        cell.markModified('cellDetails');
        await cell.save();
        if(!cell)
            return res.status(400).send('the cell cannot be updated!')
        res.send(cell);
    }
    if (Array.isArray(req.body.cellDetails)) {
        const newCellDetails = Promise.all(req.body.cellDetails.map(async (cellDetails) => {
            let newCellDetail = new CellDetail({
                temperature: cellDetails.temperature,
                current: cellDetails.current,
                voltage: cellDetails.voltage,
                percentage: cellDetails.percentage,
                dateOfRecord: cellDetails.dateOfRecord
            })
            newCellDetail = await newCellDetail.save();
            return newCellDetail._id
        }))
        const newCellDetailsIds = await newCellDetails
        let cell = await Cell.findById(car.cells[+req.params.cellNumber]);
        cell.cellDetails = newCellDetailsIds.reverse().concat(cell.cellDetails);
        cell.markModified('cellDetails')
        await cell.save();
        if (!cell)
            return res.status(400).send('the cell cannot be update!')
        res.send(cell);
    }
});

router.patch('/:id',async (req, res)=> {
    let cell = await Cell.findById(req.params.id);

    const newCellDetails = Promise.all(req.body.cellDetails.map(async (cellDetail) =>{
        let newCellDetail = new CellDetail({
            temperature: cellDetail.temperature,
            current: cellDetail.current,
            voltage:cellDetail.voltage,
            percentage:cellDetail.percentage,
            dateOfRecord: cellDetail.dateOfRecord
        })
        newCellDetail = await newCellDetail.save();
        return newCellDetail._id
    }))
    const  newCellDetailsIds = await newCellDetails
    cell.cellDetails = newCellDetailsIds.concat(cell.cellDetails)
        //cell.cellDetails.concat(newCellDetailsIds);  newCellDetailsIds.reverse()
    await cell.save();
    if(!cell)
        return res.status(400).send('the cell cannot be update!')

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
