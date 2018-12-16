Bar Chart example:

```js
function randomNumber() {
    return Math.random() * (40 - 0) + 0;
}

const data = [
    {
        key: 'Group 1',
        values: [
            { x: 'A', y: 10 },
            { x: 'B', y: 90 },
            { x: 'C', y: 171 },
            { x: 'D', y: 300 }
        ]
    },
];

<BarChart data={data} />
```