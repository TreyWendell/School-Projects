def leap_year?(year)
    if year % 4 == 0
        if year % 100 == 0
            if year % 400 == 0
                return true
            else
                return false
            end
        else
            return true
        end
    else
        return false
    end
end

puts leap_year?(2024) # Output: true
puts leap_year?(2021) # Output: false
