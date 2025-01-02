set count 0

function failure
    set count $(math $count + 1)

    set_color -o brred
    printf "failure! ($count)\n"
    set_color white
end

function succes
    set count $(math $count + 1)

    set_color -o brgreen
    printf "succes! ($count)\n"
    set_color white
end

function run
    if not binary/generate $(random) 1000000 0 1 > "resource/input.txt"
        failure
        return 1
    end

    if not binary/solve_1 < "resource/input.txt" > "resource/output_1.txt"
        failure
        return 1
    end

    if not binary/solve_4 < "resource/input.txt" > "resource/output_4.txt"
        failure
        return 1
    end

    if not diff "resource/output_1.txt" "resource/output_4.txt"
        failure
        return 1
    end

    succes
    return 0
end

make

while run
end
