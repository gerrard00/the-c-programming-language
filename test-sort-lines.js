#!/usr/bin/env node
'use strict';
const child_process = require('child_process');
const exec = child_process.exec;
const spawn = child_process.spawn;
const fileToTest = process.argv[2];

function simpleExec(cmd) {
  return new Promise((resolve, reject) => {
    console.log(cmd, '\n');

    const child = exec(cmd,
      (error, stdout, stderr) => {
        if (stdout) console.log(`stdout: ${stdout}`);
        if (stderr) console.log(`stderr: ${stderr}`);
        if (error !== null) {
          reject(error);
        }
        console.log('\n========================\n');
        resolve(0);
    });
  });
}

function runProgram(cmd, input) {
  return new Promise((resolve, reject) => {
    console.log(cmd, '\n');

    const child = spawn(cmd);

    child.on('exit', (code) => {
      console.log(`exited with code: ${code}`);
      resolve();
    });

    child.stderr.on('data', (data) => {
      reject(data);
    });

    child.stdout.on('data', (data) => {
      process.stdout.write(data);
    });

    child.stdin.on('error', error => {
      console.log(`child stdin error: ${error}`);
    });

    //TODO: how do I really handle this?
      // child.stdin.write(input.shift());
    // child.stdin.write('123\n\n');
    input.forEach(line => {
      console.log(`${line}`);
      child.stdin.write(line + '\n')
    });
  });
}

simpleExec(`clang -g -Wall -Wextra -Wpedantic -lm ${fileToTest}.c -o ${fileToTest}.o`)
  .then(() => {
    runProgram(`./${fileToTest}.o`, [
      '123',
      '7777',
      '456',
      '2',
      ''
    ])
    .then(() => {
      console.log('done!');
    })
    .catch(err => console.error(`run error: ${err}`));
  })
  .catch(err => console.log(`build error: ${err}`));
