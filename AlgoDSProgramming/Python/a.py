import pprint

strs = ["hers", "his", "herse", "rset", "ersi"]

def buildStateMachine():
    state_machine = {}
    cur_max_state = 0
    for each_str in strs:
        # Each string starts with state 0.
        current_state = 0
        for each_char in each_str:
            if current_state not in state_machine:
                cur_max_state += 1
                state_machine[current_state] = {each_char : cur_max_state}
            
            elif each_char not in state_machine[current_state]:
                cur_max_state += 1
                state_machine[current_state][each_char] = cur_max_state 

            # each char takes state machine from state a to state b.
            current_state = state_machine[current_state][each_char]

    return state_machine

state_machine = buildStateMachine()
pprint.pprint(state_machine)    

            