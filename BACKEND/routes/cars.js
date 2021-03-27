const {Car} = require('../models/car');
const express = require('express');
const { Cell } = require('../models/cell');
const router = express.Router();

router.get(`/`, async (req, res) =>{
    const carList = await Car.find().populate('user', 'name').sort({'dateOfInsertion': -1});

    if(!carList) {
        res.status(500).json({success: false})
    }
    res.send(carList);
})

router.get(`/:id`, async (req, res) =>{
    const car = await Car.findById(req.params.id)
        .populate('user', 'name')
        .populate('cells')

    if(!car) {
        res.status(500).json({success: false})
    }
    res.send(car);
})

router.post('/', async (req,res)=>{
    const cells = Promise.all(req.body.cells.map(async (cell) =>{
        let newCell = new cell({
            number: cell.number,
            model: cell.model,
            temperature: cell.temperature,
            current: cell.current,
            voltage: cell.voltage,
            status: cell.status,
            percentage: cell.percentage
        })

        newCell = await newCell.save();

        return newCell;
    }))
     const cellResolved =  await cells;
    //
    // const totalPrices = await Promise.all(orderItemsIdsResolved.map(async (orderItemId)=>{
    //     const orderItem = await OrderItem.findById(orderItemId).populate('product', 'price');
    //     const totalPrice = orderItem.product.price * orderItem.quantity;
    //     return totalPrice
    // }))
    //
    // const totalPrice = totalPrices.reduce((a,b) => a +b , 0);

    let Car = new Car({
        cells: cellResolved,
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
