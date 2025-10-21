# Run the game and immediately exit to check for memory leaks
echo "exit" | ./trading_game &
PID=$!
sleep 2
leaks $PID
